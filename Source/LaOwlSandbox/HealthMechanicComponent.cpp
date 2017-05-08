/*
This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
Attribution-NonCommercial-ShareAlike 4.0 International
LaOwlSandbox
An EscapeVelocity Production (Nate Gillard).
*/

#include "LaOwlSandbox.h"
#include "HealthMechanicComponent.h"


// Sets default values for this component's properties
UHealthMechanicComponent::UHealthMechanicComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Health = 100.f;
}


// Called when the game starts
void UHealthMechanicComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

bool UHealthMechanicComponent::IsHealthDepleted_Implementation() const {
	return !(Health > 0.0f);
}

void UHealthMechanicComponent::HealthDepleted_Implementation() {
	GetOwner()->Destroy();
}

float UHealthMechanicComponent::TakeDamage_Implementation(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) {
	Health -= DamageAmount;

	return DamageAmount;
}

// Called every frame
void UHealthMechanicComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsHealthDepleted()) {
		HealthDepleted();
	}
}

