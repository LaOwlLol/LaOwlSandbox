/*
This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
Attribution-NonCommercial-ShareAlike 4.0 International
An EscapeVelocity Production (Nate Gillard).
*/

#include "FPDev.h"
#include "ShipController.h"

AShipController::AShipController() : Super() {
	OwnedPawn= GetPawn();
}

void AShipController::AddPitchInput(float Rate)
{
	//Super::AddPitchInput(Rate);
	
	auto PitchRot = FRotator(Rate, 0, 0);
	
	//auto Transform = GetActorTransform();
	//Transform.ConcatenateRotation(PitchRot.Quaternion());
	//Transform.NormalizeRotation();
	//SetControlRotation(Transform.Rotator());
	
	auto Rotation = GetActorTransform().Rotator();
	auto NewRotation = FQuat(Rotation) * FQuat(PitchRot);
	NewRotation.Normalize();
	SetControlRotation(NewRotation.Rotator());
}

void AShipController::AddYawInput(float Rate)
{
	//Super::AddYawInput(Rate);
	
	auto YawRot = FRotator(0, Rate, 0);

	//auto Transform = GetActorTransform();
	//Transform.ConcatenateRotation(YawRot.Quaternion());
	//Transform.NormalizeRotation();
	//SetControlRotation(Transform.Rotator());
	
	auto Rotation = GetActorTransform().Rotator();
	auto NewRotation = FQuat(Rotation) * FQuat(YawRot);
	NewRotation.Normalize();
	SetControlRotation(NewRotation.Rotator());
}

void AShipController::AddRollInput(float Rate)
{
	//Super::AddRollInput(Rate);
	
	auto RollRot = FRotator(0, 0, Rate);

	//auto Transform = GetActorTransform();
	//Transform.ConcatenateRotation(RollRot.Quaternion());
	//Transform.NormalizeRotation();
	//SetControlRotation(Transform.Rotator());
	
	auto Rotation = GetActorTransform().Rotator();
	auto NewRotation = FQuat(Rotation) * FQuat(RollRot)  ;
	NewRotation.Normalize();
	SetControlRotation(NewRotation.Rotator());
}

/*void AShipController::AddInputRotation(FQuat InputRotation) {
	
	if (!OwnedCharacter) {
		return;
	}

	//auto CharacterRotation = OwnedPawn->GetActorRotation();

	OwnedPawn->SetActorRotation(FQuat(OwnedPawn->GetActorRotation())* InputRotation);
}*/
