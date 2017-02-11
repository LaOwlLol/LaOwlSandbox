// Fill out your copyright notice in the Description page of Project Settings.

#include "FPDev.h"
#include "WeaponMechanic.h"


UWeaponMechanic::UWeaponMechanic() : ShotMultiplier(1), MultiplierDelay(0.05), FireDelay(0.2), SpreadWidth(1) {

	SpreadPattern.Init(true, SpreadWidth);

}

UWeaponMechanic::UWeaponMechanic(int32 Multiplier) : ShotMultiplier(Multiplier), MultiplierDelay(0.05), FireDelay(0.2), SpreadWidth(1) {

	SpreadPattern.Init(true, SpreadWidth);

}

UWeaponMechanic::UWeaponMechanic(int32 Multiplier, const TArray<bool>& Pattern, int32 Width) : ShotMultiplier(Multiplier), MultiplierDelay(0.05), FireDelay(0.2), SpreadWidth(Width) {

	SpreadPattern = Pattern;

}

/*UWeaponMechanic::UWeaponMechanic(const UWeaponMechanic& Copy) : ShotMultiplier(Copy.ShotMultiplier), SpreadWidth(Copy.SpreadWidth) {

	SpreadPattern = Copy.SpreadPattern;

}*/

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
	
	if (FireDelay < 0.0) {
		FireDelay = 0.0;
	}
}

void UWeaponMechanic::ModifyShotMultiplierDelay(float Delay) { 
	MultiplierDelay = Delay; 
	
	if (MultiplierDelay < 0.0) {
		MultiplierDelay = 0.0;
	}
}