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
	

	//Set the ShotMuliplier.
	UFUNCTION(BlueprintCallable, Category = "Weapon Modifiers")
		void ModifyShotMultiplier(int32 Multiplier);

	//Increase the shot multiplier by a Bonus amount/
	//@Param Bonus: Amount to be added to current ShotMultiplier.
	UFUNCTION(BlueprintCallable, Category = "Weapon Modifiers")
		void UpgradeShotMultiplier(int32 Bonus) { ModifyShotMultiplier(ShotMultiplier + Bonus); }

	//Decrease the shot shot multiplier by a Penalty amount
	//@Param: Penality: a postivie amount this method will subtract from the current ShotMultiplier.
	UFUNCTION(BlueprintCallable, Category = "Weapon Modifiers")
		void DowngradeShotMultiplier(int32 Penalty) { ModifyShotMultiplier(ShotMultiplier - Penalty); }

	//Set the FireDelay.
	UFUNCTION(BlueprintCallable, Category = "Weapon Modifiers")
		void ModifyFireDelay(float Delay);

	//Increase the FireDelay by a Delta amount.
	//@Param Delta: Amount to be added to current FireDelay.
	UFUNCTION(BlueprintCallable, Category = "Weapon Modifiers")
		void IncreaseFireDelay(float Delta) { ModifyFireDelay(FireDelay + Delta); }

	//Decrease the FireDelay by a Delta amount.
	//@Param Delta: Amount to be subtracted to current FireDelay.
	UFUNCTION(BlueprintCallable, Category = "Weapon Modifiers")
		void DecreaseFireDelay(float Delta) { ModifyFireDelay(FireDelay - Delta); }

	//Set the MuiltiplierDelay.  
	UFUNCTION(BlueprintCallable, Category = "Weapon Modifiers")
		void ModifyShotMultiplierDelay(float Delay);

	//Increase the MultiplierDelay by a Delta amount.
	//@Param Delta: Amount to be added to current MultiplierDelay.
	UFUNCTION(BlueprintCallable, Category = "Weapon Modifiers")
		void IncreaseShotMultiplierDelay(float Delta) { ModifyShotMultiplierDelay(MultiplierDelay + Delta); }

	//Decrease the MultiplierDelay by a Delta amount.
	//@Param Delta: Amount to be subtracted from current MultiplierDelay.
	UFUNCTION(BlueprintCallable, Category = "Weapon Modifiers")
		void DecreaseShotMultiplierDelay(float Delta) { ModifyShotMultiplierDelay(MultiplierDelay - Delta); }

};
