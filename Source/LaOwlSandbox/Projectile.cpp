// This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License..

#include "LaOwlSandbox.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile() : BaseDamage(10.0f), ImpactVelocityTransferScale(1.0f)
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	//CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);		// set up a notification for when this component hits something blocking

																					// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->MaxSpeed = 0.f;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AProjectile::OnHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * ImpactVelocityTransferScale, GetActorLocation());

		Destroy();
	}
}

float AProjectile::GetDamage_Implementation() const
{
	return BaseDamage;
}

void AProjectile::AddVelocity(FVector Delta)
{
	GetProjectileMovement()->Velocity = GetVelocity() + Delta;
}