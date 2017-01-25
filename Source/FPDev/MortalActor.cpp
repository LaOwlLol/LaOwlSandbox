// Fill out your copyright notice in the Description page of Project Settings.

#include "FPDev.h"
#include "MortalActor.h"


// Sets default values
AMortalActor::AMortalActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Health = 100;
}

// Called when the game starts or when spawned
void AMortalActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMortalActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	if (IsHealthDepleated()) {
		HealthDepleated();
	}
}

bool AMortalActor::IsHealthDepleated_Implementation() const {
	return !(Health > 0.0);
}

void AMortalActor::HealthDepleated_Implementation() {
	Destroy();
}

float AMortalActor::TakeDamage_Implementation(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) {
	Health -= DamageAmount;

	return DamageAmount;
}