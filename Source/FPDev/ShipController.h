/*
This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
Attribution-NonCommercial-ShareAlike 4.0 International
An EscapeVelocity Production (Nate Gillard).
*/

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
