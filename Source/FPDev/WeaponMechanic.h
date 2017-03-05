// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "WeaponMechanic.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class FPDEV_API UWeaponMechanic : public UObject
{
	GENERATED_BODY()
	
public:

	//Create a Basic WeaponMechanic
	UWeaponMechanic();


	//Whether the trigger can be held to continue firing or not.
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Weapon Functionality")
		bool FullAutomatic;

	//The number of shot to fire on a single trigger pull.
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Weapon Functionality")
		int32 ShotMultiplier;

	//The Delay between projectiles spawned in a single pull of the trigger.
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Weapon Functionality")
		float MultiplierDelay;
	
	//The Delay between trigger pulls. 
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Weapon Functionality")
		float FireDelay;

	//Width of the 2D spread pattern in terms of elements.
	//Must be <= SpreadPattern.Num()
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Weapon Functionality")
		int32 SpreadWidth;

	//Height of the 2D Spread hight in terms of elements.
	UFUNCTION(BlueprintCallable, Category = "Weapon Functionality")
		int32 GetSpreadHeight() { return SpreadPattern.Num() / SpreadWidth; }

	//Width of each cell in terms of unreal engine "units".
	UFUNCTION(BlueprintCallable, Category = "Weapon Functionality")
		float GetSpreadCellDim();

	//Pattern of the projectiles fired per shot.
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Weapon Functionality")
		TArray<bool> SpreadPattern;

	//Area in terms of unreal engine "units" of the SpreadPattern as it reaches SpreadDepth
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Weapon Functionality")
		float SpreadArea;

	//Distance in terms of unreal engine "units" from the projectile spawn point SpreadPattern reaches full SpreaArea.
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Weapon Functionality")
		float SpreadDepth;

	UFUNCTION(BlueprintCallable, Category = "Weapon Modifiers")
		bool ToggleFullAutomatic() { return FullAutomatic = !FullAutomatic; }

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

	//Set the SpreadDepth to given Depth. This method checks for a minimum and does not allow the value to be set below the min for SpreadDepth. All other methods that modify SpreadDepth should be passed to this method.
	UFUNCTION(BlueprintCallable, Category = "Weapon Modifiers")
		void ModifySpreadDepth(float Depth);

	//Increase the SpreadDepth by Delta.
	UFUNCTION(BlueprintCallable, Category = "Weapon Modifiers")
		void IncreaseSpreadDepth(float Delta) { ModifySpreadDepth(SpreadDepth + Delta); }

	//Decrease the SpreadDepth by Delta.
	UFUNCTION(BlueprintCallable, Category = "Weapon Modifiers")
		void DecreaseSpreadDepth(float Delta) { ModifySpreadDepth(SpreadDepth - Delta); }

	//Set the SpreadArea to given Area. This method checks for a minimum and does not allow the vale to be set below the min for SpreadArea. All other methods that modify SpreadArea should be passed to this method.
	UFUNCTION(BlueprintCallable, Category = "Weapon Modifiers")
		void ModifySpreadArea(float Area);
	
	//Increase the SpreadArea by Delta.
	UFUNCTION(BlueprintCallable, Category = "Weapon Modifiers")
		void IncreaseSpreadArea(float Delta) { ModifySpreadArea(SpreadArea + Delta); }

	//Decrease the SpreadArea by Delta.
	UFUNCTION(BlueprintCallable, Category = "Weapon Modifiers")
		void DecreaseSpreadArea(float Delta) { ModifySpreadArea(SpreadArea - Delta); }
};
