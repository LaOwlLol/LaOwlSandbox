// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once 
#include "GameFramework/HUD.h"
#include "CanvasItem.h"
#include "FPDevHUD.generated.h"

UCLASS(Blueprintable)
class AFPDevHUD : public AHUD
{
	GENERATED_BODY()

public:

	AFPDevHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

	class APlayerController* PlayerController;
	class APlayerShip* PlayerShip;


	void DrawText(const FString& TheStr, const FLinearColor& TheColor, const float& X, const float& Y);

	void VDrawTile(UTexture2D* tex, float x, float y, const FColor& TheColor);

	void DrawWeaponMechanicPattern(float OrigX, float OrigY, const FColor & TheColor);

private:
	/** Crosshair asset pointer */
	//class UTexture2D* CrosshairTex;

	UTexture2D* PatternBulletTexture;

protected:

	UPROPERTY() TArray<class UHUDElement*> HUDElements;

	//Construct a new HUDElement and add it to this HUD's elements list
	UFUNCTION(BlueprintCallable, Category = "HUD Management")
		bool AddHUDElement(UClass* HUDElementType );

	virtual void PostInitializeComponents() override;

	FORCEINLINE class APlayerController* GetPlayerController() const { return PlayerController; }
};

