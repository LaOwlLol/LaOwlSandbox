// This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License..

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class LAOWLSANDBOX_API AProjectile : public AActor
{
	/* Private Members */

	/** Sphere collision component */
	UPROPERTY(EditDefaultsOnly, Category = "Projectile Visual Characteristics")
		class USphereComponent* CollisionComp;

	/** Projectile movement component */
	UPROPERTY(EditDefaultsOnly, Category = "Projectile Movement Characteristics", meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* ProjectileMovement;

	/* Private Methods */

	GENERATED_BODY()
	
protected:

	/* Protected  Members */

	/* Protected Methods */

public:	

	/* Public Members */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Damage")
		float BaseDamage;

	//A scaler on the transfer of velocity to physics objects impacted by this projectile.
	//For example 100.0f add 100% of this projectiles velocity as "point impluse" at contact point.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement") 
		float ImpactVelocityTransferScale;

	/* Public Members */

	// Sets default values for this actor's properties
	AProjectile();

	/** called when projectile hits something */
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	//Allows the designer to define how damage is calculated for the projectile.
	//Default Return Value: 10.0f
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Projectile Characteristics") 
		float GetDamage() const;
	virtual float GetDamage_Implementation() const;

	void AddVelocity(FVector Delta);

	/** Returns CollisionComp subobject **/
	FORCEINLINE class USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
};
