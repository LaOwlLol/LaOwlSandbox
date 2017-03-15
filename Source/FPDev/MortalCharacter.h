// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Animation/AnimInstance.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "MortalInterface.h"
#include "WeaponComponent.h"
#include "WeaponMechanic.h"
#include "FPDevProjectile.h"
#include "MortalCharacter.generated.h"

UCLASS(Blueprintable)
class FPDEV_API AMortalCharacter : public ACharacter, public IMortalInterface
{
	GENERATED_BODY()

	//List of rounds queued to fire.
	TArray<bool> FireQueue;

	//Whether the character is holding the trigger down or not.
	bool TriggerHeld;

	//Spwan bullets for the round.
	void FireWeapon(float DeltaTime);

protected:
	
	virtual void SetupCharacterView();

	virtual class USkeletalMeshComponent* GetCharaterUsedMesh();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Change TriggerHeld state
	void ToggleTrigger() {
		TriggerHeld = !TriggerHeld;
	}

	//Fire Event Triggered by input.
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

public:	

	// Sets default values for this character's properties
	AMortalCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Projectile class to spawn */
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Projectile")
		TSubclassOf<class AFPDevProjectile> ProjectileClass;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	class UWeaponComponent* WeaponComponent = NULL;

	//Attach a weaponComponent of CompClass to
	//Each derived class implements this method to attach weapon.
	UFUNCTION(BlueprintCallable, Category = "Weapon")
		virtual bool AttachWeapon(UClass* ComponentClass);

	//Fire Event Triggered by input.
	UFUNCTION(BlueprintCallable, Category = "Weapon Operation")
		bool ActivateWeapon();
	

	//UFUNCTION(BlueprintCallable, Category = "Weapon")
	//	bool DetachWeapon();

	//The characters WeaponMechanic, used to specify "how the character uses" the current weapon.
	//See WeaponMechanics for "Weapon Functionality".
	//Get the character's WeaponFunction member and use "Weapon Modifier" functions to modify the active WeaponMechanic's "Weapon Functionality" properties. 
	UPROPERTY(BlueprintReadOnly, Category = "Weapon Mechanic")
		UWeaponMechanic* WeaponFunction;

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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
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

};
