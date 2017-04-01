// Fill out your copyright notice in the Description page of Project Settings.

#include "FPDev.h"
#include "ShipController.h"

AShipController::AShipController() : Super() {
	OwnedPawn= GetControlledPawn();
}

void AShipController::AddPitchInput(float Rate)
{
	
	
	auto PitchRot = FRotator(Rate, 0, 0);
	
	auto Transform = GetActorTransform();
	Transform.ConcatenateRotation(PitchRot.Quaternion());
	Transform.NormalizeRotation();
	SetControlRotation(Transform.Rotator());
	
	//auto Rotation = GetActorTransform().Rotator();
	//auto NewRotation = FQuat(PitchRot) * FQuat(Rotation);
	//NewRotation.Normalize();
	//SetControlRotation(NewRotation.Rotator());
}

void AShipController::AddYawInput(float Rate)
{
	
	
	auto YawRot = FRotator(0, Rate, 0);

	auto Transform = GetActorTransform();
	Transform.ConcatenateRotation(YawRot.Quaternion());
	Transform.NormalizeRotation();
	SetControlRotation(Transform.Rotator());
	
	//auto Rotation = GetActorTransform().Rotator();
	//auto NewRotation = FQuat(YawRot) * FQuat(Rotation);
	//NewRotation.Normalize();
	//SetControlRotation(NewRotation.Rotator());
}

void AShipController::AddRollInput(float Rate)
{
	
	
	auto RollRot = FRotator(0, 0, Rate);

	auto Transform = GetActorTransform();
	Transform.ConcatenateRotation(RollRot.Quaternion());
	Transform.NormalizeRotation();
	SetControlRotation(Transform.Rotator());
	
	//auto Rotation = GetActorTransform().Rotator();
	//auto NewRotation = FQuat(RollRot) * FQuat(Rotation);
	//NewRotation.Normalize();
	//SetControlRotation(NewRotation.Rotator());
}

/*void AShipController::AddInputRotation(FQuat InputRotation) {
	
	if (!OwnedCharacter) {
		return;
	}

	//auto CharacterRotation = OwnedPawn->GetActorRotation();

	OwnedPawn->SetActorRotation(FQuat(OwnedPawn->GetActorRotation())* InputRotation);
}*/
