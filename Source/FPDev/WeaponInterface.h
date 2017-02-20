// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WeaponInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UWeaponInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
 * 
 */
class FPDEV_API IWeaponInterface
{
	GENERATED_IINTERFACE_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	//Check if the weapon has a sound to play on activation. 
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Gameplay)
		bool HasActivationSound() const;

	//Return the ActivationSound sound.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Gameplay)
	class USoundBase* GetActivationSound() const;

	//Check if the weapon has an animation to play on activation. 
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Gameplay)
		bool HasActivationAnimation() const;

	//Return the ActivationAnitmation.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Gameplay)
	class UAnimMontage* GetActivationAnimation() const;

	
};
