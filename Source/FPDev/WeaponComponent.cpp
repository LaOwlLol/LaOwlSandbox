/*
This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
Attribution-NonCommercial-ShareAlike 4.0 International
An EscapeVelocity Production (Nate Gillard).
*/

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
