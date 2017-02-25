// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "MortalInterface.h"
#include "WeaponComponent.h"
#include "WeaponMechanic.h"
#include "FPDevCharacter.generated.h"

class UInputComponent;

UCLASS(Blueprintable)
class AFPDevCharacter : public ACharacter, public IMortalInterface
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	class USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	TArray<bool> FireQueue;
	

public:
	AFPDevCharacter();

	virtual void BeginPlay();

	// Called every frame
	virtual void Tick(float DeltaSeconds);

	/** Projectile class to spawn */
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Projectile")
		TSubclassOf<class AFPDevProjectile> ProjectileClass;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	class UWeaponComponent* FP_Gun = NULL;

	//Attach a weaponComponent of CompClass to 
	UFUNCTION(BlueprintCallable, Category = "Weapon")
		bool AttachWeapon(UClass* ComponentClass);

	//UFUNCTION(BlueprintCallable, Category = "Weapon")
	//	bool DetachWeapon();

	UPROPERTY(BlueprintReadOnly, Category = "Weapon Mechanic")
		class UWeaponMechanic* WeaponFunction;

	UFUNCTION(BlueprintCallable, Category = "Weapon Mechanic")
		void ChangeWeaponMechanicClass(UClass* NewMechanicType);

	UFUNCTION(BlueprintCallable, Category = "Weapon Mechanic")
		void SetWeaponFunction(UWeaponMechanic* NewWeaponFunction);

	//Time since the last trigger pulled.
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Weapon Mechanic")
		float TimeSinceFire;

	//Time since the last round fired.
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Weapon Mechanic")
	float TimeSinceBulletSpawn;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Mesh)
	class USceneComponent* FP_MuzzleLocation;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	//Remaining health (basic implentation)
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Health System") int32 Health;

	//Check if health is remaining
	//Default: false if health > 0.0 
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Health System")
		bool IsHealthDepleated() const;
	virtual bool IsHealthDepleated_Implementation() const override;

	//Event called when IsHealthDepleated is true.
	//Default: destroy this character.
	//Recommended to always end by destroy this character.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Health System")
		void HealthDepleated();
	virtual void HealthDepleated_Implementation() override;

	//Apply damage.
	//Default: Health -= DamageAmount.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Damage")
		float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser);
	virtual float TakeDamage_Implementation(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

protected:
	
	/** Fires a projectile. */
	void OnFire();

	/** Resets HMD orientation and position in VR. */
	void OnResetVR();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	struct TouchData
	{
		TouchData() { bIsPressed = false;Location=FVector::ZeroVector;}
		bool bIsPressed;
		ETouchIndex::Type FingerIndex;
		FVector Location;
		bool bMoved;
	};
	void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location);
	TouchData	TouchItem;
	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	/* 
	 * Configures input for touchscreen devices if there is a valid touch interface for doing so 
	 *
	 * @param	InputComponent	The input component pointer to bind controls to
	 * @returns true if touch controls were enabled.
	 */
	bool EnableTouchscreenMovement(UInputComponent* InputComponent);

public:
	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};

