/*
This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
Attribution-NonCommercial-ShareAlike 4.0 International
An EscapeVelocity Production (Nate Gillard).
*/

#pragma once

#include "MortalPawn.h"
#include "ShipPawn.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class FPDEV_API AShipPawn : public AMortalPawn
{
	GENERATED_BODY()

	//List of rounds queued to fire.
	TArray<bool> FireQueue;

	//Whether the character is holding the trigger down or not.
	bool TriggerHeld;

	//Spwan bullets for the round.
	void FireWeapon(float DeltaTime);
	
	class AShipController* ShipController;

public:

	AShipPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(EditDefaultsOnly, Category = "Controller")
		float BaseTurnRate;

	// Base roll rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(EditDefaultsOnly, Category = "Controller")
		float BaseRollRate;

	// Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(EditDefaultsOnly, Category = "Controller")
		float BaseLookUpRate;

	UPROPERTY(EditDefaultsOnly, Category = "Controller")
		float FlightControlFactor;
	
	//Called via input to turn at a given rate.
	//@param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	void TurnAtRate(float Rate);
	
	//Called via input to turn look up/down at a given rate.
	//@param Rate in range -1.0 to 1.0
	void PitchAtRate(float Rate);

	//Called via input to roll left at a given rate.
	//@param Rate in range -1.0 to 0.0
	void RollLeft(float Rate);

	//Called via input to roll right at a given rate.
	//@param Rate in range 0.0 to 1.0
	void RollRight(float Rate);

	////Called via input to roll at a given rate.
	//@param Rate in range -1.0 to 1.0
	void RollAtRate(float Rate);

	//Modify Engine acceleration impules by Rate input.
	//@Param: Rate -1.0 to 1.0 typically from Controller (Player or AI) input.
	void ModifyEngineImpluse(float Rate);

	//Fire Event Triggered by input.
	void OnFire();

	//Change TriggerHeld state
	void ToggleTrigger() {
		TriggerHeld = !TriggerHeld;
	}

	// Projectile class to spawn when trigger is pulled.
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Projectile")
		TSubclassOf<class AFPDevProjectile> ProjectileClass;

	//The characters WeaponMechanic, used to specify "how the character uses" the current weapon.
	//See WeaponMechanics for "Weapon Functionality".
	//Get the character's WeaponFunction member and use "Weapon Modifier" functions to modify the active WeaponMechanic's "Weapon Functionality" properties. 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon Mechanic")
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
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon Mechanic")
	class USceneComponent* MuzzleLocation;

	//Fire Event Triggered by input.
	UFUNCTION(BlueprintCallable, Category = "Weapon Operation")
		bool ActivateWeapon();

	//This ship ImpulseEngine 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Impulse Engine")
	class UImpulseEngineComponent* ImpulseEngine;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//initialize the pawn's mesh and other viewable components
	virtual void SetupPawnView() override;

	//initialize the ships engie component.
	virtual void SetupImpulseEngine();

	//Temp holder for firing sounds
	//TODO move to weapon component if refactor requirs.
	//See: https://github.com/LaOwlLol/FPDev/issues/3
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gameplay SFX")
	class USoundBase* WeaponActivationSound;

	//Return the mesh component(s) used for this pawn.
	virtual UStaticMeshComponent* GetPawnUsedView() override;

};
