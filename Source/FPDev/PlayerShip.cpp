// Fill out your copyright notice in the Description page of Project Settings.

#include "FPDev.h"
#include "PlayerShip.h"


APlayerShip::APlayerShip()  {

	SetupPawnView();

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

void APlayerShip::SetupPawnView()
{
	
	//construct camera compoenent.
	BoomArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("BoomArm"));
	BoomArm->SetupAttachment(GetPawnUsedView());
	BoomArm->bUsePawnControlRotation = true;

	BoomCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("BoomCamera"));
	BoomCamera->SetupAttachment(BoomArm);

}

UStaticMeshComponent* APlayerShip::GetPawnUsedView()
{
	return Super::GetPawnUsedView();
}

void APlayerShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerShip::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	//Bind input actions to functions.
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AShipPawn::OnFire);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AShipPawn::ToggleTrigger);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AShipPawn::ToggleTrigger);

	//Bind input axis to functions.
	PlayerInputComponent->BindAxis("Turn", this, &AShipPawn::TurnAtRate);
	PlayerInputComponent->BindAxis("TurnRate", this, &AShipPawn::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &AShipPawn::PitchAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AShipPawn::PitchAtRate);
	PlayerInputComponent->BindAxis("Impulse", this, &AShipPawn::ModifyEngineImpluse);
	PlayerInputComponent->BindAxis("Thruster", this, &AShipPawn::ModifyEngineImpluse);
	PlayerInputComponent->BindAxis("Break", this, &AShipPawn::ModifyEngineImpluse);
	PlayerInputComponent->BindAxis("RollRight", this, &AShipPawn::RollRight);
	PlayerInputComponent->BindAxis("RollLeft", this, &AShipPawn::RollLeft);
}

void APlayerShip::BeginPlay()
{
	Super::BeginPlay();
}

