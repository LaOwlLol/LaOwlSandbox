/*
This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
Attribution-NonCommercial-ShareAlike 4.0 International
LaOwlSandbox
An EscapeVelocity Production (Nate Gillard).
*/

#include "LaOwlSandbox.h"
#include "HealthMechanicComponent.h"
#include "MortalPawn.h"


// Sets default values
AMortalPawn::AMortalPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMortalPawn::BeginPlay()
{
	Super::BeginPlay();
	
	SetupHealthSystem();
}

float AMortalPawn::TakeDamage_Implementation(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	//If our health system is active, take damage. 
	if (HealthComponent) {
		HealthComponent->TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	}

	return DamageAmount;
}

void AMortalPawn::SetupHealthSystem()
{
	//if a HealthMechanicComponent type is selected in the blueprint.
	if (HealthMechanicType) {
		//conststruct the type selected.  
		HealthComponent = NewObject<UHealthMechanicComponent>(this, GetUsedHealthMechanicType(), TEXT("Health"));
	}
	else {
		//construct a default health system. 
		HealthComponent = NewObject<UHealthMechanicComponent>(this, TEXT("Health"));
	}

	if (HealthComponent) {
		HealthComponent->RegisterComponent();
	}
}

UClass * AMortalPawn::GetUsedHealthMechanicType()
{
	//return the blueprint selected UHealthMechanicComponent type.
	return HealthMechanicType;
}

// Called every frame
void AMortalPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


/*
// Called to bind functionality to input
void AMortalPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
*/

