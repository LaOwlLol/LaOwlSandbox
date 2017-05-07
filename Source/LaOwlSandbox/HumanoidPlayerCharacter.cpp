/*
This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
Attribution-NonCommercial-ShareAlike 4.0 International
LaOwlSandbox
An EscapeVelocity Production (Nate Gillard).
*/

#include "LaOwlSandbox.h"
#include "GameFramework/InputSettings.h"
#include "HumanoidPlayerCharacter.h"

void AHumanoidPlayerCharacter::BeginPlay() {
	Super::BeginPlay();
}

void AHumanoidPlayerCharacter::SetupPlayerInputComponent(class UInputComponent * PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AArmedCharacter::OnFire);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AArmedCharacter::ToggleTrigger);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AArmedCharacter::ToggleTrigger);

	PlayerInputComponent->BindAxis("WalkForward", this, &AHumanoidCharacter::MoveForward);
	PlayerInputComponent->BindAxis("WalkRight", this, &AHumanoidCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" is an absolute delta, such as a mouse, is feed directly to add yaw input.
	// "turnrate" is a rate of change, such as an analog joystick, pass to TurnAtRate
	PlayerInputComponent->BindAxis("MouseLookRight", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("GamepadLookRight", this, &AHumanoidCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("MouseLookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("GamepadLookUp", this, &AHumanoidCharacter::LookUpAtRate);
}

AHumanoidPlayerCharacter::AHumanoidPlayerCharacter()
{
}

void AHumanoidPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
