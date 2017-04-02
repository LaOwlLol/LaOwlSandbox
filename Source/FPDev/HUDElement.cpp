// Fill out your copyright notice in the Description page of Project Settings.

#include "FPDev.h"
#include "FPDevHUD.h"
#include "HUDElement.h"

void UHUDElement::RegisterOwner_Implementation(AFPDevHUD* Owner)
{
	OwnerHUD = Owner; 
}

void UHUDElement::Draw_Implementation() const
{
	if (!OwnerHUD) { return; }
	
	OwnerHUD->DrawText(FString("DefualtHUDElement"), ColorProperties, XOrigin, YOrigin);
}
