/*
This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
Attribution-NonCommercial-ShareAlike 4.0 International
An EscapeVelocity Production (Nate Gillard).
*/

#pragma once

#include "Components/PrimitiveComponent.h"
#include "ImpulseEngineComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class FPDEV_API UImpulseEngineComponent : public UPrimitiveComponent
{
	GENERATED_BODY()
	
	//list of impulse queued for the ship's "ImpulseEngine".
	TArray<float> ImpulseQueue;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Movement Characteristics")
		bool HoverAllowed;

	//The ships base line Movement Scaler.  When Hover is not allowed ship trend toward's thier CruiseImpluse Scaler.
	UPROPERTY(EditDefaultsOnly, Category = "Movement Characteristics")
		float CruiseImpulse;

	//Impluse Increase Modification Scalar.  
	//This is the base scalar to (InputRate *  BaseAccelerationRate  * DeltaTime) formula
	//InputRate is the GamePad or Keyboard input.
	//DeltaTime is the input EventPolling rate, typically much less that .01 seconds.
	UPROPERTY(EditDefaultsOnly, Category = "Movement Characteristics")
		float BaseAccelerationRate;

	//Impluse decrease Modification Scalar.  
	//This is the base scalar to (InputRate *  BaseDecelerationRate  * DeltaTime) formula
	//InputRate is the GamePad or Keyboard input.
	//DeltaTime is the input EventPolling rate, typically much less that .01 seconds.
	UPROPERTY(EditDefaultsOnly, Category = "Movement Characteristics")
		float BaseBreakRate;

	//Decay to Thrust base Scalar.
	UPROPERTY(EditDefaultsOnly, Category = "Movement Characteristics")
		float BaseImpulseDecayRate;

	//Decay to Break base Scalar.
	UPROPERTY(EditDefaultsOnly, Category = "Movement Characteristics")
		float BaseBreakDecayRate;

	//Current Engine Impluse Scalar.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement Characteristics")
		float EngineImpulse;

	//Max Engine Impluse Scalar.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Characteristics")
		float MaxEngineImpulse;

	//Min Engine Impluse Scalar.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Characteristics")
		float MinEngineImpulse;
	
public:

	UImpulseEngineComponent();

	void AddEngineImpulse(float Rate);

	UFUNCTION(BlueprintCallable, Category = "Movement Characteristics")
		bool GetHoverAllowed() { return HoverAllowed; }

	//The ships base line Movement Scaler.  When Hover is not allowed ship trend toward's thier CruiseImpluse Scaler.
	UFUNCTION(BlueprintCallable, Category = "Movement Characteristics")
		float GetCruiseImpulse() { return CruiseImpulse; }

	//Impluse Increase Modification Scalar.  
	UFUNCTION(BlueprintCallable, Category = "Movement Characteristics")
		float GetBaseAccelerationRate() { return BaseAccelerationRate; }

	//Impluse decrease Modification Scalar.  
	UFUNCTION(BlueprintCallable, Category = "Movement Characteristics")
		float GetBaseBreakRate() { return BaseBreakRate; }

	//Decay to Thrust base Scalar.
	UFUNCTION(BlueprintCallable, Category = "Movement Characteristics")
		float GetBaseImpulseDecayRate() { return BaseImpulseDecayRate; }

	//Decay to Break base Scalar.
	UFUNCTION(BlueprintCallable, Category = "Movement Characteristics")
		float GetBaseBreakDecayRate() { return BaseBreakDecayRate; }

	//Current Engine Impluse Scalar.
	UFUNCTION(BlueprintCallable, Category = "Movement Characteristics")
		float GetEngineImpulse() { return EngineImpulse; }

	//Max Engine Impluse Scalar.
	UFUNCTION(BlueprintCallable, Category = "Movement Characteristics")
		float GetMaxEngineImpulse() { return MaxEngineImpulse; }

	//Min Engine Impluse Scalar.
	UFUNCTION(BlueprintCallable, Category = "Movement Characteristics")
		float GetMinEngineImpulse() { return MinEngineImpulse; }

	//Tick Helper method for applying velocity.
	void OnEngineImpluse(float DeltaTime);

	//Tick Helper for resumne cruise velocity when there is no Trust/Break (ImpulseMod) on active input. 
	void OnEngineCruise(float DeltaTime);

};
