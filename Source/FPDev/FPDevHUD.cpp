// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "FPDev.h"
#include "FPDevHUD.h"
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
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	DrawWeaponMechanicPattern(Center.X, Center.Y-(Canvas->ClipY * 0.125f), FColor::Red);

	// offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
	//const FVector2D CrosshairDrawPosition( (Center.X),
										   //(Center.Y + 20.0f));

	// draw the crosshair
	//FCanvasTileItem TileItem( CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	//TileItem.BlendMode = SE_BLEND_Translucent;
	//Canvas->DrawItem( TileItem );
}

void AFPDevHUD::DrawText(UFont * TheFont, const FString & TheStr, const float & X, const float & Y, const FLinearColor & TheColor, const float & TheScale, bool DrawOutline, const FLinearColor OutlineColor)
{

	if (!Canvas) {
		return;
	}

	//Text and Font
	FCanvasTextItem NewText(FVector2D(X, Y), FText::FromString(TheStr), TheFont, TheColor);

	//Text Scale
	NewText.Scale.Set(TheScale, TheScale);

	//Outline gets its alpha from the main color
	NewText.bOutlined = true;
	NewText.OutlineColor = OutlineColor;
	NewText.OutlineColor.A = TheColor.A * 2;

	//Draw
	Canvas->DrawItem(NewText);
}

void AFPDevHUD::VDrawTile(UTexture2D * tex, float x, float y, const FColor & TheColor)
{
	if (!Canvas) return;
	if (!tex) return;
	//~

	Canvas->SetDrawColor(TheColor);

	FCanvasTileItem TileItem( FVector2D(x,y), tex->Resource, TheColor);
	TileItem.BlendMode = SE_BLEND_Translucent;

	//Draw
	Canvas->DrawItem( TileItem );
}

void AFPDevHUD::DrawWeaponMechanicPattern(float OrigX, float OrigY, const FColor & TheColor)
{
	UWeaponMechanic* WeaponFunction = PlayerShip->WeaponFunction;
	float HUD_Scale = (Canvas->ClipX / Canvas->ClipY) * 5.0f;
	float offSetW = (float(WeaponFunction->SpreadWidth) / 2.0f);
	float offSetH = (float(WeaponFunction->GetSpreadHeight()) / 2.0f);
	float Dim = WeaponFunction ->GetSpreadCellDim();
	int32 i = 0;
	//for each element or cell in the SpreadPattern array.
	for (auto& cell : WeaponFunction->SpreadPattern) {
		if (cell) {
			//transform Pattern index to x and y coordinates
			float x = ((i%WeaponFunction->SpreadWidth)  -  offSetW) * (Dim * HUD_Scale) ;
			float y = ((i / WeaponFunction->SpreadWidth) -  offSetH) * (Dim * HUD_Scale) ;

			VDrawTile(PatternBulletTexture, OrigX+x, OrigY+y, TheColor);
		}

		++i;
	}
}

void AFPDevHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PlayerController = GetOwningPlayerController();

	PlayerShip = Cast<APlayerShip>(GetOwningPawn());

}
