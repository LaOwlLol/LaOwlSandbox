// This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License..

#include "LaOwlSandbox.h"
#include "ImpulseEngineComponent.h"
#include "ShipCharacter.h"

void AShipCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetupImpulseEngine();
}

void AShipCharacter::SetupImpulseEngine()
{
	//TODO this is gross see issue # on Github.
	if (ImpulseEngineType) {
		ImpulseEngineComponent = NewObject<UImpulseEngineComponent>(this, GetUsedImpulseEngineType(), TEXT("ImpulseEngine"));
		
		UImpulseEngineComponent* MyMovementComp = Cast<UImpulseEngineComponent>(GetMovementComponent());
		MyMovementComp->CopyEngineCharacteristics(ImpulseEngineComponent);

		ImpulseEngineComponent = MyMovementComp;
		ImpulseEngineComponent->UpdatedComponent = RootComponent;
	}

	/*if (ImpulseEngineComponent) {
		ImpulseEngineComponent->RegisterComponent();
		
		
	}*/
}

UClass * AShipCharacter::GetUsedImpulseEngineType()
{
	return ImpulseEngineType;
}

void AShipCharacter::YawAtRate(float Rate)
{
	if (ImpulseEngineComponent) {
		float YawMod = Rate * ((ImpulseEngineComponent->GetMinEngineImpulse()) / (FlightControlFactor * ImpulseEngineComponent->GetEngineImpulse())) * BaseYawRate * GetWorld()->GetDeltaSeconds();
		AddControllerYawInput(YawMod);
	}
}

void AShipCharacter::PitchAtRate(float Rate)
{
	if (ImpulseEngineComponent) {
		float PitchMod = Rate * ((ImpulseEngineComponent->GetMinEngineImpulse()) / (FlightControlFactor * ImpulseEngineComponent->GetEngineImpulse())) * BasePitchRate * GetWorld()->GetDeltaSeconds();
		AddControllerPitchInput(PitchMod);
	}
}

void AShipCharacter::RollAtRate(float Rate)
{
	float RollMod = Rate * BaseRollRate * GetWorld()->GetDeltaSeconds();
	AddControllerRollInput(RollMod);
}

void AShipCharacter::ModifyEngineImpulse(float Rate)
{
	if (!FMath::IsNearlyZero(Rate)) {
		if (ImpulseEngineComponent) {
			ImpulseEngineComponent->AddEngineImpulse(Rate);
		}
	}
}


AShipCharacter::AShipCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UImpulseEngineComponent>(ACharacter::CharacterMovementComponentName))
{
	BaseYawRate = 45.f;
	BasePitchRate = 45.f;
	BaseRollRate = 45.f;
	FlightControlFactor = 2.f;
}

	void AShipCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
