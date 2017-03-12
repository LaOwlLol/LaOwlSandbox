// Fill out your copyright notice in the Description page of Project Settings.


#include "FPDev.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "NPCController.h"


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