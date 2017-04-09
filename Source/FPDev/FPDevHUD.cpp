/*
This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
Attribution-NonCommercial-ShareAlike 4.0 International
An EscapeVelocity Production (Nate Gillard).

This code based on work under
Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
*/

#include "FPDev.h"
#include "FPDevHUD.h"
#include "HUDElement.h"
#include "PlayerShip.h"
#include "WeaponMechanic.h"
#include "Engine/Canvas.h"
#include "TextureResource.h"
#include "CanvasItem.h"

AFPDevHUD::AFPDevHUD()
{
	// Set the crosshair texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshiarTexObj(TEXT("/Game/FirstPerson/Textures/FirstPersonCrosshair"));
	//CrosshairTex = CrosshiarTexObj.Object;
	PatternBulletTexture = CrosshiarTexObj.Object;
}


void AFPDevHUD::DrawHUD()
{
	Super::DrawHUD();

	// Draw very simple crosshair

	// find center of the Canvas
	const FVector2D Center(0.5f, 0.5f);

	//DrawWeaponMechanicPattern(Center.X - 0.005, Center.Y-(Center.Y/4.f), FColor::Red);


	for (UHUDElement* It : HUDElements)
	{
		It->Draw();
	}

	// offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas


	VDrawTile(PatternBulletTexture, Center.X, Center.Y - (Center.Y / 4.f), FColor::Red);
	// draw the crosshair
	//FCanvasTileItem TileItem( CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	//TileItem.BlendMode = SE_BLEND_Translucent;
	//Canvas->DrawItem( TileItem );
}

void AFPDevHUD::DrawText(const FString & TheStr, const FLinearColor & TheColor, const float & X, const float & Y)
{
	if (!Canvas) return;

	Super::DrawText(TheStr, TheColor, Canvas->ClipX * X, Canvas->ClipY * Y);
}

void AFPDevHUD::VDrawTile(UTexture2D * tex, float x, float y, const FColor & TheColor)
{
	if (!Canvas) return;
	if (!tex) return;
	//~

	Canvas->SetDrawColor(TheColor);

	float w = tex->GetSurfaceWidth() / 2.f; 
	float h = tex->GetSurfaceHeight() / 2.f;

	FCanvasTileItem TileItem( FVector2D((Canvas->ClipX * x) - w, (Canvas->ClipY * y) - h), tex->Resource, TheColor);
	TileItem.BlendMode = SE_BLEND_Translucent;

	//Draw
	Canvas->DrawItem( TileItem );
}

void AFPDevHUD::DrawWeaponMechanicPattern(float OrigX, float OrigY, const FColor & TheColor)
{
	UWeaponMechanic* WeaponFunction = PlayerShip->WeaponFunction;
	float HUD_Scale = (Canvas->ClipX / Canvas->ClipY) * 0.01f;
	float offSetW = (float(WeaponFunction->SpreadWidth) / 2.0f);
	float offSetH = (float(WeaponFunction->GetSpreadHeight()) / 2.0f);
	float Dim = WeaponFunction->GetSpreadCellDim()  ;
	float EvenOffW = ((WeaponFunction->SpreadWidth % 2 == 0) ? Dim / 2.0f : 0.0);
	float EvenOffH = ((WeaponFunction->GetSpreadHeight() % 2 == 0) ? Dim / 2.0f : 0.0);
	int32 i = 0;
	//for each element or cell in the SpreadPattern array.
	for (auto& cell : WeaponFunction->SpreadPattern) {
		if (cell) {
			//transform Pattern index to x and y coordinates
			float x = ((i%WeaponFunction->SpreadWidth) - offSetW) * Dim;// +EvenOffW;
			float y = ((i / WeaponFunction->SpreadWidth) - offSetH) * Dim;// +EvenOffH;

			VDrawTile(PatternBulletTexture, OrigX + (x *HUD_Scale), OrigY + (y*HUD_Scale), TheColor);
		}
		++i;
	}
}

bool AFPDevHUD::AddHUDElement(UClass* HUDElementType)
{
	UHUDElement* newObject = NewObject<UHUDElement>(this, HUDElementType);
	if (!newObject) { return false; }
	newObject->RegisterOwner(this);
	HUDElements.Add(newObject);

	return true;
}

void AFPDevHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PlayerController = GetOwningPlayerController();
	PlayerShip = Cast<APlayerShip>(GetOwningPawn());

}
