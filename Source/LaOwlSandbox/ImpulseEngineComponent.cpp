/*
This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
Attribution-NonCommercial-ShareAlike 4.0 International
LaOwlSandbox
An EscapeVelocity Production (Nate Gillard).
*/

#include "LaOwlSandbox.h"
#include "ImpulseEngineComponent.h"

UImpulseEngineComponent::UImpulseEngineComponent()
{
	BaseAccelerationRate = 1000.0f;
	BaseBreakRate = 800.00f;
	BaseImpulseDecayRate = 500.0f;
	BaseBreakDecayRate = 500.0f;

	CruiseImpulse = 600.f;
	MaxEngineImpulse = 1500.f;
	MinEngineImpulse = 400.f;

	SetMovementMode(EMovementMode::MOVE_Custom, 0);
}

void UImpulseEngineComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	//Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Make sure that everything is still valid, and that we are allowed to move.
	if (!CharacterOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	OnEngineImpluse(DeltaTime);

	const FVector WorldMove = GetEngineImpulse() * DeltaTime * CharacterOwner->GetActorForwardVector();
	CharacterOwner->AddActorWorldOffset(WorldMove, false);
}

void UImpulseEngineComponent::BeginPlay()
{
	Super::BeginPlay();

	EngineImpulse = CruiseImpulse;
}

void UImpulseEngineComponent::OnEngineImpluse(float DeltaTime) {

	if (ImpulseQueue.Num() != 0) {
		if (ImpulseQueue[0] > 0.0) {
			EngineImpulse += ImpulseQueue[0] * BaseAccelerationRate * DeltaTime;
		}
		else {
			EngineImpulse += ImpulseQueue[0] * BaseBreakRate * DeltaTime;
		}

		EngineImpulse = FMath::Clamp(EngineImpulse, MinEngineImpulse, MaxEngineImpulse);
		ImpulseQueue.RemoveAt(0);
	}
	else {
		OnEngineCruise(DeltaTime);
	}

}

void UImpulseEngineComponent::OnEngineCruise(float DeltaTime) {
	if (EngineImpulse > CruiseImpulse) {
		if (FMath::IsNearlyEqual(EngineImpulse, CruiseImpulse, (BaseImpulseDecayRate / 10.0f))) {
			EngineImpulse = CruiseImpulse;
		}
		else {
			EngineImpulse -= BaseImpulseDecayRate * DeltaTime;
		}

		EngineImpulse = FMath::Clamp(EngineImpulse, MinEngineImpulse, MaxEngineImpulse);
	}
	else if (EngineImpulse < CruiseImpulse) {
		if (FMath::IsNearlyEqual(EngineImpulse, CruiseImpulse, (BaseBreakDecayRate / 10.0f))) {
			EngineImpulse = CruiseImpulse;
		}
		else {
			EngineImpulse += BaseBreakDecayRate * DeltaTime;
		}

		EngineImpulse = FMath::Clamp(EngineImpulse, MinEngineImpulse, MaxEngineImpulse);
	}
}

void UImpulseEngineComponent::CopyEngineCharacteristics(const UImpulseEngineComponent* temp)
{
	BaseAccelerationRate = temp->GetBaseAccelerationRate();
	BaseBreakRate = temp->GetBaseBreakRate();
	BaseImpulseDecayRate = temp->GetBaseImpulseDecayRate();
	BaseBreakDecayRate = temp->GetBaseBreakDecayRate();

	CruiseImpulse = temp->GetCruiseImpulse();
	MaxEngineImpulse = temp->GetMaxEngineImpulse();
	MinEngineImpulse = temp->GetMinEngineImpulse();
}

void UImpulseEngineComponent::AddEngineImpulse(float Rate)
{
	ImpulseQueue.Add(Rate);
}