// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectileInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UProjectileInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
 * 
 */
class FPDEV_API IProjectileInterface
{
	GENERATED_IINTERFACE_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	//Allows the designer to define how damage is calculated for the projectile.
	UFUNCTION(BlueprintImplementableEvent, Category = "Projectile Characteristics") float GetDamage() const;

};
