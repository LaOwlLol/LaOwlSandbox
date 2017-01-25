// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MortalInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class UMortalInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
 * 
 */
class FPDEV_API IMortalInterface
{
	GENERATED_IINTERFACE_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	//check if health is depleated.  Override to define when death occurs.
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Health System")
		bool IsHealthDepleated() const;

	//Event HealthDepleated.  Override with functionality or effects of death.
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Health System")
		void HealthDepleated();

	//Called by Appl<type>Damage.  Override to define effect of Damage to this actor type. 
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Damage")
		float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser);
};
