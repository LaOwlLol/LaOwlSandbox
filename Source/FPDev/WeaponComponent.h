// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SkeletalMeshComponent.h"
#include "WeaponComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class FPDEV_API UWeaponComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()
	
public:

	UWeaponComponent();

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AFPDevProjectile> ProjectileClass;
	
	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gameplay)
	FVector GunOffset;
	
	/** Sound to play each time we fire */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation;
};
