// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "MortalCharacter.h"
#include "NonPlayerCharacter.generated.h"

UCLASS(Blueprintable)
class FPDEV_API ANonPlayerCharacter : public AMortalCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANonPlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnyWhere, Category = Pawn)
	class UBehaviorTree* BehaviorTree;
};
