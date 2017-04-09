/*
This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
Attribution-NonCommercial-ShareAlike 4.0 International
An EscapeVelocity Production (Nate Gillard).
*/

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
