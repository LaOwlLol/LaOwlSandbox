/*
This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
Attribution-NonCommercial-ShareAlike 4.0 International
An EscapeVelocity Production (Nate Gillard).

This code based on work under
Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
*/

#include "FPDev.h"
#include "FPDevGameMode.h"
#include "FPDevHUD.h"
#include "PlayerShip.h"
#include "ShipController.h"

AFPDevGameMode::AFPDevGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/TestPlayerShip"));
	DefaultPawnClass = APlayerShip::StaticClass();
	
	//setup player controller as ship controller.
	PlayerControllerClass = AShipController::StaticClass();

	// use our custom HUD class
	static ConstructorHelpers::FClassFinder<AFPDevHUD> HUDClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/MyFPDevHUD"));
	HUDClass = HUDClassFinder.Class;
	//HUDClass = AFPDevHUD::StaticClass();
}
