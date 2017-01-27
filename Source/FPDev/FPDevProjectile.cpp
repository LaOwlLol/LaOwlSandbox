// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "FPDev.h"
#include "FPDevProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

AFPDevProjectile::AFPDevProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AFPDevProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	ProjectileMovement = InitProjectileMovementComponent();

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void AFPDevProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 10.0f, GetActorLocation());

		Destroy();
	}
}

UProjectileMovementComponent*  AFPDevProjectile::InitProjectileMovementComponent_Implementation() {
	// Use a ProjectileMovementComponent to govern this projectile's movement
	UProjectileMovementComponent* PMC = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	PMC->UpdatedComponent = CollisionComp;

	return PMC;
}