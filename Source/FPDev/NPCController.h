/*
This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
Attribution-NonCommercial-ShareAlike 4.0 International
An EscapeVelocity Production (Nate Gillard).
*/

#pragma once

#include "AIController.h"
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
