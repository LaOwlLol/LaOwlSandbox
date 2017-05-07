/*
This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
Attribution-NonCommercial-ShareAlike 4.0 International
LaOwlSandbox
An EscapeVelocity Production (Nate Gillard).
*/

#include "LaOwlSandbox.h"
#include "WeaponMechanicComponent.h"


// Sets default values for this component's properties
UWeaponMechanicComponent::UWeaponMechanicComponent() : FullAutomatic(false), ShotMultiplier(1), MultiplierDelay(0.05f), FireDelay(0.15f), SpreadWidth(1), SpreadDepth(10.0f), SpreadArea(10.0f) {

	SpreadPattern.Init(false, SpreadWidth);
	SpreadPattern[0] = true;

	// off to improve performance.
	PrimaryComponentTick.bCanEverTick = false;

}

// Called when the game starts
void UWeaponMechanicComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

float UWeaponMechanicComponent::GetSpreadCellDim() {
	float TotalX = SpreadWidth + GetSpreadHeight();
	float RatioAreaToX = SpreadArea / TotalX;

	return sqrt(RatioAreaToX);
}

bool UWeaponMechanicComponent::ChangePattern(const TArray<bool>& NewPattern, int32 Width) {
	if (Width <= NewPattern.Num()) {
		SpreadWidth = Width;
		SpreadPattern = NewPattern;

		return true;
	}

	return false;
}

void UWeaponMechanicComponent::ModifyShotMultiplier(int32 Multiplier) {
	ShotMultiplier = Multiplier;

	if (ShotMultiplier < 1) {
		ShotMultiplier = 1;
	}

	//reset our fire delay to check it for validity and set if to minimum fire delay if invalid.
	ModifyFireDelay(FireDelay);
}


void UWeaponMechanicComponent::ModifyFireDelay(float Delay) {
	FireDelay = Delay;

	if (FireDelay < ShotMultiplier * MultiplierDelay) {
		FireDelay = ShotMultiplier * MultiplierDelay;
	}
}

void UWeaponMechanicComponent::ModifyShotMultiplierDelay(float Delay) {
	MultiplierDelay = Delay;

	if (MultiplierDelay < 0.001f) {
		MultiplierDelay = 0.001f;
	}

	//reset our fire delay to check it for validity and set if to minimum fire delay if invalid.
	ModifyFireDelay(FireDelay);
}

void UWeaponMechanicComponent::ModifySpreadDepth(float Depth) {
	SpreadDepth = Depth;

	if (SpreadDepth < 1.0f) {
		SpreadDepth = 1.0f;
	}
}

void UWeaponMechanicComponent::ModifySpreadArea(float Area) {
	SpreadArea = Area;

	if (SpreadArea < 1.0f) {
		SpreadArea = 1.0f;
	}
}
