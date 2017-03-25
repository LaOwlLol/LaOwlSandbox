// Fill out your copyright notice in the Description page of Project Settings.

#include "FPDev.h"
#include "Components/MeshComponent.h"
#include "MortalPawn.h"


// Sets default values
AMortalPawn::AMortalPawn() : Super()
{

	SetupPawnView();

	Health = 100.0f;

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AMortalPawn::SetupPawnView()
{
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->AttachTo(RootComponent);
	BodyMesh->bCastDynamicShadow = true;
	BodyMesh->CastShadow = true;
}

UStaticMeshComponent* AMortalPawn::GetPawnUsedView()
{
	return BodyMesh;
}

// Called when the game starts or when spawned
void AMortalPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMortalPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsHealthDepleated()) {
		HealthDepleated();
	}
}

// Called to bind functionality to input
void AMortalPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

//check is health 0.0 or less.
bool AMortalPawn::IsHealthDepleated_Implementation() const {
	return !(Health > 0.0);
}

void AMortalPawn::HealthDepleated_Implementation() {
	Destroy();
}

float AMortalPawn::TakeDamage_Implementation(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) {
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Health -= DamageAmount;

	return DamageAmount;
}