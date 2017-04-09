/*
This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
Attribution-NonCommercial-ShareAlike 4.0 International
An EscapeVelocity Production (Nate Gillard).
*/

#pragma once

#include "UObject/NoExportTypes.h"
#include "HUDElement.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class FPDEV_API UHUDElement : public UObject
{
	GENERATED_BODY()
	
protected:

	class AFPDevHUD* OwnerHUD;

	//Screen X location.
	UPROPERTY(EditDefaultsOnly, Category = "Location") float XOrigin;

	//Screen Y location.
	UPROPERTY(EditDefaultsOnly, Category = "Location") float YOrigin;

	UPROPERTY(EditDefaultsOnly, Category = "Color")  FLinearColor ColorProperties;
	

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "HUD Registation")
		void RegisterOwner(AFPDevHUD* Owner);
	virtual void  RegisterOwner_Implementation(AFPDevHUD* Owner);

	//Draw the HUD element's individual components. 
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Gameplay)
		void Draw() const;
	virtual void Draw_Implementation() const;
	
};
