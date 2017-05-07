// This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License..

#include "LaOwlSandbox.h"
#include "GameFramework/InputSettings.h"
#include "ShipPlayerCharacter.h"

void AShipPlayerCharacter::BeginPlay() {
	Super::BeginPlay();
}

void AShipPlayerCharacter::SetupPlayerInputComponent(class UInputComponent * PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AArmedCharacter::OnFire);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AArmedCharacter::ToggleTrigger);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AArmedCharacter::ToggleTrigger);

	PlayerInputComponent->BindAxis("EngineImpulse", this, &AShipCharacter::ModifyEngineImpulse);

	PlayerInputComponent->BindAxis("ShipYawRight", this, &AShipCharacter::YawAtRate);
	PlayerInputComponent->BindAxis("ShipPitchUp", this, &AShipCharacter::PitchAtRate);
	PlayerInputComponent->BindAxis("ShipRollRight", this, &AShipCharacter::RollAtRate);
}

AShipPlayerCharacter::AShipPlayerCharacter()
{
}

void AShipPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
