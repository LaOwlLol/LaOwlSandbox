// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "WeaponMechanic.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class FPDEV_API UWeaponMechanic : public UObject
{
	GENERATED_BODY()

protected:

	//Width of the 2D spread pattern.
	//Must be <= SpreadPattern.Num()
	UPROPERTY(BlueprintReadOnly, Category = "Weapon Functionality")
		int32 SpreadWidth;

	//Pattern of the projectiles fired per shot.
	UPROPERTY(BlueprintReadOnly, Category = "Weapon Functionality")
		TArray<bool> SpreadPattern;
	
public:

	//Create a Basic WeaponMechanic
	
	UWeaponMechanic();

	//Create basic Multishot WeaponMechanic
	UWeaponMechanic(int32 Multiplier);

	//Create custome WeaponMechanic
	UWeaponMechanic(int32 Multiplier, const TArray<bool>& Pattern, int32 Width);

	//Create custome WeaponMecahnic by copying one.
	//UWeaponMechanic(const UWeaponMechanic& Copy);

	//The number of shot to fire on a single trigger pull.
	UPROPERTY(BlueprintReadWrite, VisibleAnyWhere, Category = "Weapon Functionality")
		int32 ShotMultiplier;

	//The Delay between projectiles spawned in a single pull of the trigger.
	UPROPERTY(BlueprintReadWrite, VisibleAnyWhere, Category = "Weapon Functionality")
		float MultiplierDelay;
	
	//The Delay between trigger pulls. 
	UPROPERTY(BlueprintReadWrite, VisibleAnyWhere, Category = "Weapon Functionality")
		float FireDelay;

	UFUNCTION(BlueprintCallable, Category = "Weapon Functionality")
		TArray<bool> GetSpreadPattern() { return SpreadPattern; }

	UFUNCTION(BlueprintCallable, Category = "Weapon Functionality")
		int32 GetSpreadWidth() { return SpreadWidth; }

	//Set the Spread Pattern from an array given the width
	//Width must be  0 > and <= NewPattern.Num() (size or length of array)
	//Return:  False if failed to set this SpreadPattern to NewPattern with Given width (ie Width > NewPattern.Num())
	UFUNCTION(BlueprintCallable, Category = "Weapon Modifiers")
		bool ChangePattern(const TArray<bool>& NewPattern, int32 Width);
	
	UFUNCTION(BlueprintCallable, Category = "Weapon Modifiers")
		void ModifyShotMultiplier(int32 Multiplier);

	UFUNCTION(BlueprintCallable, Category = "Weapon Modifiers")
		void ModifyFireDelay(float Delay) { FireDelay = Delay; }

	UFUNCTION(BlueprintCallable, Category = "Weapon Modifiers")
		void ModifyMultiplierDelay(float Delay) { MultiplierDelay = Delay; }

	UFUNCTION(BlueprintCallable, Category = "Weapon Modifiers")
		void UpgradeShotMultiplier(int32 Bonus);

	UFUNCTION(BlueprintCallable, Category = "Weapon Modifiers")
		void DowngradeShotMultiplier(int32 Penalty);

};
