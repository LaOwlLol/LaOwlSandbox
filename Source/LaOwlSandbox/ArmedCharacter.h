/*
This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
Attribution-NonCommercial-ShareAlike 4.0 International
LaOwlSandbox
An EscapeVelocity Production (Nate Gillard).
*/

#pragma once

#include "MortalCharacter.h"
#include "ArmedCharacter.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class LAOWLSANDBOX_API AArmedCharacter : public AMortalCharacter
{
	/* Private Members */
	
	//List of rounds queued to fire.
	TArray<bool> FireQueue;
	
	//Whether the character is holding the trigger down or not.
	bool TriggerHeld;

	/* Private Methods */

	GENERATED_BODY()

	//Spwan bullets for the round.
	void FireWeapon(float DeltaTime);
	
protected:

	/*Protected  Members */

	//the type of weaon mechanic (UWeaponMechanicComponent subclass) to use for this class. 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<class UWeaponMechanicComponent> WeaponMechanicType;
	
	//Weapon Mechanic determines how the current weapon fires.
	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
		class UWeaponMechanicComponent* WeaponMechanic;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	class AWeaponEntity* WeaponEntity;

	//Time since the last trigger pulled.
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Weapon")
		float TimeSinceFire;

	//Time since the last round fired.
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Weapon")
		float TimeSinceBulletSpawn;

	//Projectile class to spawn when trigger is pulled.
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Weapon")
		TSubclassOf<class AProjectile> ProjectileClass;

	/*Protected  Methods */

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Called on BeginPlay and used to lazy instantiation the Weapon Mechanic to the type selected by subclasses.
	virtual void SetupWeaponMechanic();

	//Called on SetupHealthSystem to get the blueprint selected Weapon Mechanic type at runtime.
	virtual UClass* GetUsedWeaponMechanicType();

public:

	/* Public Members */

	/* Public Methods */

	AArmedCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual FVector GetMovementVelocity();

	//Attach a WeaponEntityComponent of WeaponClass to
	//Each derived class implements this method to attach weapon.
	UFUNCTION(BlueprintCallable, Category = "Weapon")
		virtual bool AttachWeapon(UClass* WeaponClass);

	//Fire Event Triggered by input.
	void OnFire();

	//Change TriggerHeld state
	void ToggleTrigger() {
		TriggerHeld = !TriggerHeld;
	}

	//Fire Event Triggered by input.
	UFUNCTION(BlueprintCallable, Category = "Weapon Operation")
		bool ActivateWeapon();

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
