/*
This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
Attribution-NonCommercial-ShareAlike 4.0 International
An EscapeVelocity Production (Nate Gillard).
*/

#pragma once

#include "HUDElement.h"
#include "ImpulseEngineHUDElement.generated.h"

/**
 * 
 */
UCLASS()
class FPDEV_API UImpulseEngineHUDElement : public UHUDElement
{
	GENERATED_BODY()

protected:
	
	class APlayerShip* PlayerShip;

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "HUD Registation")
		void RegisterOwner(AFPDevHUD* Owner);
	virtual void  RegisterOwner_Implementation(AFPDevHUD* Owner);

	//Draw the HUD element's individual components. 
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Gameplay)
		void Draw() const;
	virtual void Draw_Implementation() const;

	
	
};
