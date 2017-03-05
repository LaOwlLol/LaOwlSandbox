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

	bool TriggerHeld;

	void ToggleTrigger() {
		TriggerHeld = !TriggerHeld;
	}
	
	void FireWeapon(float DeltaTime);

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

	//The characters WeaponMechanic, used to specify "how the character uses" the current weapon.
	//See WeaponMechanics for "Weapon Functionality".
	//Get the character's WeaponFunction member and use "Weapon Modifier" functions to modify the active WeaponMechanic's "Weapon Functionality" properties. 
	UPROPERTY(BlueprintReadOnly, Category = "Weapon Mechanic")
		class UWeaponMechanic* WeaponFunction;

	//Use this function change the character's WeaponFunction to a new WeaponMechanic of your choice.
	//This method constructs a WeaponMechanic of your choice and makes it the acitive WeaponFunction.
	//@Params: NewMechanicType - the WeaponMechanic subclass to change to.
	//DO NOT: Pass this function a WeaponMechanic object.  
	UFUNCTION(BlueprintCallable, Category = "Weapon Mechanic")
		void ChangeWeaponMechanicClass(UClass* NewMechanicType);

	//Use this function change the character's WeaponFunction to a WeaponMechanic object.
	//This method sets the acitive WeaponFunction to a WeaponMechanic object.
	//@Params: NewWeaponFunction - the WeaponMechanic object to change to.
	//DO NOT: Pass this function a WeaponMechanic type.  
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
	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};

