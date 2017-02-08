// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "FPDev.h"
#include "FPDevGameMode.h"
#include "FPDevHUD.h"
#include "FPDevCharacter.h"

AFPDevGameMode::AFPDevGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPDevHUD::StaticClass();
}
