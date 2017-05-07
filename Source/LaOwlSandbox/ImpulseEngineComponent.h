/*
This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
Attribution-NonCommercial-ShareAlike 4.0 International
LaOwlSandbox
An EscapeVelocity Production (Nate Gillard).
*/

#pragma once

#include "GameFramework/CharacterMovementComponent.h"
#include "ImpulseEngineComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class LAOWLSANDBOX_API UImpulseEngineComponent : public UCharacterMovementComponent
{
	/* Private Members */

	//list of impulse queued for the ship's "ImpulseEngine".
	TArray<float> ImpulseQueue;

	/* Private Methods */

	GENERATED_BODY()
	
protected:

	/* Protected Members */

	UPROPERTY(EditDefaultsOnly, Category = "Impulse Engine Characteristics")
		bool HoverAllowed;

	//The ships base line Movement Scaler.  When Hover is not allowed ship trend toward's thier CruiseImpluse Scaler.
	UPROPERTY(EditDefaultsOnly, Category = "Impulse Engine Characteristics")
		float CruiseImpulse;

	//Impluse Increase Modification Scalar.  
	//This is the base scalar to (InputRate *  BaseAccelerationRate  * DeltaTime) formula
	//InputRate is the GamePad or Keyboard input.
	//DeltaTime is the input EventPolling rate, typically much less that .01 seconds.
	UPROPERTY(EditDefaultsOnly, Category = "Impulse Engine Characteristics")
		float BaseAccelerationRate;

	//Impluse decrease Modification Scalar.  
	//This is the base scalar to (InputRate *  BaseDecelerationRate  * DeltaTime) formula
	//InputRate is the GamePad or Keyboard input.
	//DeltaTime is the input EventPolling rate, typically much less that .01 seconds.
	UPROPERTY(EditDefaultsOnly, Category = "Impulse Engine Characteristics")
		float BaseBreakRate;

	//Decay to Thrust base Scalar.
	UPROPERTY(EditDefaultsOnly, Category = "Impulse Engine Characteristics")
		float BaseImpulseDecayRate;

	//Decay to Break base Scalar.
	UPROPERTY(EditDefaultsOnly, Category = "Impulse Engine Characteristics")
		float BaseBreakDecayRate;

	//Current Engine Impluse Scalar.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Impulse Engine Characteristics")
		float EngineImpulse;

	//Max Engine Impluse Scalar.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Impulse Engine Characteristics")
		float MaxEngineImpulse;

	//Min Engine Impluse Scalar.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Impulse Engine Characteristics")
		float MinEngineImpulse;
	
	/* Protected Methods */

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public: 

	/* Public Members */

	/* Public Methods */
	UImpulseEngineComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddEngineImpulse(float Rate);

	UFUNCTION(BlueprintCallable, Category = "Movement Characteristics")
		bool GetHoverAllowed() const { return HoverAllowed; }

	//The ships base line Movement Scaler.  When Hover is not allowed ship trend toward's thier CruiseImpluse Scaler.
	UFUNCTION(BlueprintCallable, Category = "Movement Characteristics")
		float GetCruiseImpulse() const { return CruiseImpulse; }

	//Impluse Increase Modification Scalar.  
	UFUNCTION(BlueprintCallable, Category = "Movement Characteristics")
		float GetBaseAccelerationRate() const { return BaseAccelerationRate; }

	//Impluse decrease Modification Scalar.  
	UFUNCTION(BlueprintCallable, Category = "Movement Characteristics")
		float GetBaseBreakRate() const { return BaseBreakRate; }

	//Decay to Thrust base Scalar.
	UFUNCTION(BlueprintCallable, Category = "Movement Characteristics")
		float GetBaseImpulseDecayRate() const { return BaseImpulseDecayRate; }

	//Decay to Break base Scalar.
	UFUNCTION(BlueprintCallable, Category = "Movement Characteristics")
		float GetBaseBreakDecayRate() const { return BaseBreakDecayRate; }

	//Current Engine Impluse Scalar.
	UFUNCTION(BlueprintCallable, Category = "Movement Characteristics")
		float GetEngineImpulse() const { return EngineImpulse; }

	//Max Engine Impluse Scalar.
	UFUNCTION(BlueprintCallable, Category = "Movement Characteristics")
		float GetMaxEngineImpulse() const { return MaxEngineImpulse; }

	//Min Engine Impluse Scalar.
	UFUNCTION(BlueprintCallable, Category = "Movement Characteristics")
		float GetMinEngineImpulse() const { return MinEngineImpulse; }

	//Tick Helper method for applying velocity.
	void OnEngineImpluse(float DeltaTime);

	//Tick Helper for resumne cruise velocity when there is no Trust/Break (ImpulseMod) on active input. 
	void OnEngineCruise(float DeltaTime);

	void CopyEngineCharacteristics(const UImpulseEngineComponent* temp);

};
