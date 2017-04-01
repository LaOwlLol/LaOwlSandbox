// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "ShipController.generated.h"

/**
 * 
 */
UCLASS()
class FPDEV_API AShipController : public APlayerController
{
	GENERATED_BODY()

		AActor* OwnedPawn;
public:
	AShipController();
	
	void AddPitchInput(float Rate) override;
	void AddYawInput(float Rate) override;
	void AddRollInput(float Rate) override;

protected:

	
	
};
