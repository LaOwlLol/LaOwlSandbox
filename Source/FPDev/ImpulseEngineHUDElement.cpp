// Fill out your copyright notice in the Description page of Project Settings.

#include "FPDev.h"
#include "FPDevHUD.h"
#include "PlayerShip.h"
#include "Math/Rotator.h"
#include "ImpulseEngineHUDElement.h"

void UImpulseEngineHUDElement::RegisterOwner_Implementation(AFPDevHUD* Owner) {
	OwnerHUD = Owner;
	PlayerShip = Cast<APlayerShip>(OwnerHUD->PlayerShip);
}

void UImpulseEngineHUDElement::Draw_Implementation() const {

	if (!OwnerHUD) { 
		//OwnerHUD->DrawText(FString("n"), ColorProperties, XOrigin, YOrigin);
		return;
	}
	if (!PlayerShip) {
		OwnerHUD->DrawText(FString("No InpulseEngine Info!"), ColorProperties, XOrigin, YOrigin);
		return;
	}

	//OwnerHUD->DrawText( FString("Accelerating: ").Append(
		//FString::SanitizeFloat(PlayerShip->Acceleration)),
		//ColorProperties, XOrigin, YOrigin-0.02f);
	OwnerHUD->DrawText( FString("EngineImpluse: ").Append(
		FString::SanitizeFloat(PlayerShip->EngineImpulse)),
		ColorProperties, XOrigin, YOrigin);
	OwnerHUD->DrawText(FString("Pitch: ").Append(
		FString::SanitizeFloat(PlayerShip->GetActorRotation().Pitch)),
		ColorProperties, XOrigin, YOrigin+0.02f);
	OwnerHUD->DrawText(FString("Yaw: ").Append(
		FString::SanitizeFloat(PlayerShip->GetActorRotation().Yaw)),
		ColorProperties, XOrigin, YOrigin + 0.04f);
	OwnerHUD->DrawText(FString("Roll: ").Append(
		FString::SanitizeFloat(PlayerShip->GetActorRotation().Roll)),
		ColorProperties, XOrigin, YOrigin + 0.06f);

}