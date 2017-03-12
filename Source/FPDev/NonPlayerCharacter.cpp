// Fill out your copyright notice in the Description page of Project Settings.

#include "FPDev.h"
#include "NonPlayerCharacter.h"


// Sets default values
ANonPlayerCharacter::ANonPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMovementComponent()->NavAgentProps.AgentHeight = 320.0f;
	GetMovementComponent()->NavAgentProps.AgentRadius = 160.0f;

}

// Called when the game starts or when spawned
void ANonPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANonPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
