// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once 
#include "GameFramework/HUD.h"
#include "CanvasItem.h"
#include "FPDevHUD.generated.h"

UCLASS()
class AFPDevHUD : public AHUD
{
	GENERATED_BODY()

public:

	AFPDevHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

	class APlayerController* PlayerController;
	class APlayerShip* PlayerShip;

	void DrawText(UFont* TheFont, const FString& TheStr, const float& X, const float& Y, const FLinearColor& TheColor,
		const float& TheScale, bool DrawOutline = false, const FLinearColor OutlineColor = FLinearColor(0, 0, 0, 1)); 

	void VDrawTile(UTexture2D* tex, float x, float y, const FColor& TheColor);

	void DrawWeaponMechanicPattern(float OrigX, float OrigY, const FColor & TheColor);

private:
	/** Crosshair asset pointer */
	//class UTexture2D* CrosshairTex;

	UTexture2D* PatternBulletTexture;

protected:

	virtual void PostInitializeComponents() override;

	FORCEINLINE class APlayerController* GetPlayerController() const { return PlayerController; }
};

