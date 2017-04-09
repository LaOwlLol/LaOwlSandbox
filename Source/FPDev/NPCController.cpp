/*
This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
Attribution-NonCommercial-ShareAlike 4.0 International
An EscapeVelocity Production (Nate Gillard).
*/


#include "FPDev.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "NPCController.h"
#include "NonPlayerCharacter.h"


ANPCController::ANPCController() {
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	check(BlackboardComp);
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComp"));
	check(BehaviorTreeComp)
}

void ANPCController::Possess(APawn* InPawn) {
	Super::Possess(InPawn);

	ANonPlayerCharacter* possessedPawn = Cast<ANonPlayerCharacter>(InPawn);

	if (InPawn != nullptr) {
		BlackboardComp->InitializeBlackboard(*(possessedPawn->BehaviorTree->BlackboardAsset));

		BehaviorTreeComp->StartTree(*(possessedPawn->BehaviorTree));
	}
}

UBlackboardComponent* ANPCController::GetBlackboard() {
	return BlackboardComp;
}