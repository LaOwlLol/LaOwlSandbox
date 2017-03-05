// Fill out your copyright notice in the Description page of Project Settings.

#include "FPDev.h"
#include "WeaponMechanic.h"


UWeaponMechanic::UWeaponMechanic() : FullAutomatic(false), ShotMultiplier(1), MultiplierDelay(0.05f), FireDelay(0.2f), SpreadWidth(3), SpreadDepth(100.0f), SpreadArea(4.0f) {

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
}


void UWeaponMechanic::ModifyFireDelay(float Delay) { 
	FireDelay = Delay; 
	
	if (FireDelay < 0.0f) {
		FireDelay = 0.0f;
	}
}

void UWeaponMechanic::ModifyShotMultiplierDelay(float Delay) { 
	MultiplierDelay = Delay; 
	
	if (MultiplierDelay < 0.0f) {
		MultiplierDelay = 0.0f;
	}
}

void UWeaponMechanic::ModifySpreadDepth(float Depth) {
	SpreadDepth = Depth;

	if (SpreadDepth < 0.0f) {
		SpreadDepth = 0.0f;
	}
}

void UWeaponMechanic::ModifySpreadArea(float Area) {
	SpreadArea = Area;

	if (SpreadArea < 0.0f) {
		SpreadArea = 0.0f;
	}
}