// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTService.h"
#include "AgroCheck.generated.h"

/**
 * 
 */
UCLASS()
class FPDEV_API UAgroCheck : public UBTService
{
	GENERATED_BODY()

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	UBehaviorTree* ThisTree;
	class ANPCController* ThisController;
	class ANonPlayerCharacter* ThisAICharacter;
	
};
