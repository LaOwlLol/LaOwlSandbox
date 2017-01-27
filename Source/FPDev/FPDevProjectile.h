// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Actor.h"
#include "ProjectileInterface.h"
#include "FPDevProjectile.generated.h"

UCLASS(config=Game)
class AFPDevProjectile : public AActor, public IProjectileInterface
{
	GENERATED_BODY()

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	class USphereComponent* CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;

public:
	AFPDevProjectile();

	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	//Allows desginer to construct a UProjectileMovementComponent to govern this projectile's movement of a a custom projectile type.
	//Default Behavoir: construct a ProjectileMovementComponent and connect it to the Collision Component. 
	//Default Return Value: 
	UFUNCTION(BlueprintNativeEvent, Category = "Projectile Characteristics") UProjectileMovementComponent* InitProjectileMovementComponent();
	virtual UProjectileMovementComponent* InitProjectileMovementComponent_Implementation();

	//Allows the designer to define how damage is calculated for the projectile.
	//Default Return Value: 10.0f
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Projectile Characteristics") float GetDamage() const;
	virtual float GetDamage_Implementation() const;

	/** Returns CollisionComp subobject **/
	FORCEINLINE class USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
};

