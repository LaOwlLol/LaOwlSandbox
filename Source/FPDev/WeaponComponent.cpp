// Fill out your copyright notice in the Description page of Project Settings.

#include "FPDev.h"
#include "WeaponComponent.h"


UWeaponComponent::UWeaponComponent() : Super() {
	
	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);
	//GunOffset = FVector(0.0f, 0.0f, 0.0f);
}