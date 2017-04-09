/*
This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
Attribution-NonCommercial-ShareAlike 4.0 International
An EscapeVelocity Production (Nate Gillard).
*/

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
