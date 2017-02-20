// Fill out your copyright notice in the Description page of Project Settings.

#include "FPDev.h"
#include "WeaponComponent.h"


UWeaponComponent::UWeaponComponent() : Super() {
	
}

class USoundBase* UWeaponComponent::GetActivationSound_Implementation() const {
	return ActivationSound;
}

class UAnimMontage* UWeaponComponent::GetActivationAnimation_Implementation() const {
	return ActivationAnimation;
}
