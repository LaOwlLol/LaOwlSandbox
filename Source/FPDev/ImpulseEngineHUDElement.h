// Fill out your copyright notice in the Description page of Project Settings.

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
