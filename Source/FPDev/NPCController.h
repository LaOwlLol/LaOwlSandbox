// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "NonPlayerCharacter.h"

#include "NPCController.generated.h"

/**
 * 
 */
UCLASS()
class FPDEV_API ANPCController : public AAIController
{
	GENERATED_BODY()
	
public:

	ANPCController();
	virtual void Possess(APawn* InPawn) override;

	UBlackboardComponent* GetBlackboard();

protected:

	UPROPERTY(BlueprintReadWrite, category = Behavior)
	class UBlackboardComponent* BlackboardComp;

	UPROPERTY(BlueprintReadWrite, category = Behavior)
	class UBehaviorTreeComponent* BehaviorTreeComp;

};
