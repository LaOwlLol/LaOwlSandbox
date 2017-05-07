/*
This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
Attribution-NonCommercial-ShareAlike 4.0 International
LaOwlSandbox
An EscapeVelocity Production (Nate Gillard).
*/

#pragma once

#include "GameFramework/Character.h"
#include "MortalCharacter.generated.h"

UCLASS(Blueprintable)
class LAOWLSANDBOX_API AMortalCharacter : public ACharacter
{
	/* Private Members */

	/* Private Methods */

	GENERATED_BODY()

protected:

	/*Protected  Members */

	//The type of health system (HealthMechanicComponet subclass) to use for this class.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health Meachanic")
		TSubclassOf<class UHealthMechanicComponent> HealthMechanicType;

	//Heath system or UHealthMechanicComponent. 
	UPROPERTY(BlueprintReadOnly, Category = "Health Mechanic")
	class UHealthMechanicComponent* HealthComponent;

	/*Protected  Methods */

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Called internally by the egine when Apply<Type>Damage is called.
	//Try calling ApplyPointDamage on a component's OnHit Event.
	UFUNCTION(BlueprintNativeEvent, Category = "Damage")
		float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser);
	virtual float TakeDamage_Implementation(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser);

	//Called on BeginPlay and used to lazy instantiation the health system to the type selected by subclasses.
	virtual void SetupHealthSystem();

	//Called on SetupHealthSystem to get the blueprint selected health system at runtime.
	virtual UClass* GetUsedHealthMechanicType();

public:	

	/* Public Members */

	/* Public Methods */

	AMortalCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
