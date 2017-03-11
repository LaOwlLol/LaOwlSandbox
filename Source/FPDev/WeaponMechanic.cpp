// Fill out your copyright notice in the Description page of Project Settings.

#include "FPDev.h"
#include "WeaponMechanic.h"


UWeaponMechanic::UWeaponMechanic() : FullAutomatic(false), ShotMultiplier(1), MultiplierDelay(0.05f), FireDelay(0.15f), SpreadWidth(3), SpreadDepth(10.0f), SpreadArea(10.0f) {

	SpreadPattern.Init(false, SpreadWidth);
	SpreadPattern[1] = true;

}

float UWeaponMechanic::GetSpreadCellDim() { 
	float TotalX = SpreadWidth + GetSpreadHeight();
	float RatioAreaToX = SpreadArea / TotalX;

	return sqrt(RatioAreaToX); 
}

bool UWeaponMechanic::ChangePattern(const TArray<bool>& NewPattern, int32 Width) {
	if (Width <= NewPattern.Num()) {
		SpreadWidth = Width;
		SpreadPattern = NewPattern;

		return true;
	}

	return false;
}

void UWeaponMechanic::ModifyShotMultiplier(int32 Multiplier) {
	ShotMultiplier = Multiplier;

	if (ShotMultiplier < 1) {
		ShotMultiplier = 1;
	}

	//reset our fire delay to check it for validity and set if to minimum fire delay if invalid.
	ModifyFireDelay(FireDelay);
}


void UWeaponMechanic::ModifyFireDelay(float Delay) { 
	FireDelay = Delay; 
	
	if (FireDelay < ShotMultiplier * MultiplierDelay) {
		FireDelay = ShotMultiplier * MultiplierDelay;
	}
}

void UWeaponMechanic::ModifyShotMultiplierDelay(float Delay) { 
	MultiplierDelay = Delay; 
	
	if (MultiplierDelay < 0.001f) {
		MultiplierDelay = 0.001f;
	}

	//reset our fire delay to check it for validity and set if to minimum fire delay if invalid.
	ModifyFireDelay(FireDelay);
}

void UWeaponMechanic::ModifySpreadDepth(float Depth) {
	SpreadDepth = Depth;

	if (SpreadDepth < 1.0f) {
		SpreadDepth = 1.0f;
	}
}

void UWeaponMechanic::ModifySpreadArea(float Area) {
	SpreadArea = Area;

	if (SpreadArea < 1.0f) {
		SpreadArea = 1.0f;
	}
}