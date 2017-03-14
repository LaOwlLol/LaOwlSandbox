// Fill out your copyright notice in the Description page of Project Settings.

#include "FPDev.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BehaviorTree/BehaviorTree.h"
#include "NPCController.h"
#include "NonPlayerCharacter.h"
#include "DrawDebugHelpers.h"
#include "AgroCheck.h"

void UAgroCheck::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (ThisTree == nullptr || ThisController == nullptr || ThisAICharacter == nullptr) {
		ThisTree = OwnerComp.GetCurrentTree();

		ThisController = Cast<ANPCController>(OwnerComp.GetAIOwner());

		ThisAICharacter = Cast<ANonPlayerCharacter>(ThisController->GetPawn());

		if (ThisTree == nullptr || ThisController == nullptr || ThisAICharacter == nullptr) {
			UE_LOG(LogTemp, Warning, TEXT("Warning Agro Service perfromed on invalid AI"));
			return;
		}
	}

	//Init sweep parms struct with trace complex set to true
	FCollisionQueryParams SphereSweepParams(FName(TEXT("AgroCheckSweep")), true, ThisAICharacter);

	//channel should match player channel
	FCollisionObjectQueryParams ObjectQuery(ECC_GameTraceChannel2);
	
	//init hit result
	FHitResult HitOut(ForceInit);

	//draw some helpful debugs...
	DrawDebugSphere(ThisAICharacter->GetWorld(), ThisAICharacter->GetActorLocation(), 1500, 12, FColor::Red, false, 4.0f);

	//sweep test
	bool bResult = ThisAICharacter->GetWorld()->SweepSingleByObjectType(HitOut, 
		ThisAICharacter->GetActorLocation(),
		ThisAICharacter->GetActorLocation() + FVector(0.0f, 0.0f, 10.0f),
		FQuat(), ObjectQuery,
		FCollisionShape::MakeSphere(1500),
		SphereSweepParams);

	if (bResult) {
		ThisController->GetBlackboard()->SetValueAsObject(TEXT("ToFollow"), HitOut.GetActor());

		ThisController->GetBlackboard()->SetValueAsVector(TEXT("Home"), ThisAICharacter->GetActorLocation());

		ThisController->GetBlackboard()->SetValueAsVector(TEXT("Target"), HitOut.GetActor()->GetActorLocation() );
	}
	else {
		ThisController->GetBlackboard()->SetValueAsObject(TEXT("ToFollow"), nullptr);
	}
}




