/*
This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
Attribution-NonCommercial-ShareAlike 4.0 International
LaOwlSandbox
An EscapeVelocity Production (Nate Gillard).
*/

#pragma once

#include "ArmedCharacter.h"
#include "ShipCharacter.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class LAOWLSANDBOX_API AShipCharacter : public AArmedCharacter
{
	/* Private Members */

	/* Private Methods */

	GENERATED_BODY()
	
	
protected:

	/*Protected  Members */
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controller")
		float BaseYawRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controller")
		float BasePitchRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controller")
		float BaseRollRate;

	UPROPERTY(EditDefaultsOnly, Category = "Controller")
		float FlightControlFactor;

	//The type of health system (HealthMechanicComponet subclass) to use for this class.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Impulse Engine")
		TSubclassOf<class UImpulseEngineComponent>  ImpulseEngineType;

	//Heath system or UHealthMechanicComponent. 
	UPROPERTY(BlueprintReadOnly, Category = "Impulse Engine")
	class UImpulseEngineComponent* ImpulseEngineComponent;

	/*Protected  Methods */

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetupImpulseEngine();

	virtual UClass* GetUsedImpulseEngineType();

public:

	/* Public Members */

	/* Public Methods */

	AShipCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Called via input to turn at a given rate.
	//@param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	void YawAtRate(float Rate);

	//Called via input to turn look up/down at a given rate.
	//@param Rate in range -1.0 to 1.0
	void PitchAtRate(float Rate);

	////Called via input to roll at a given rate.
	//@param Rate in range -1.0 to 1.0
	void RollAtRate(float Rate);

	//Modify Engine acceleration impules by Rate input.
	//@Param: Rate -1.0 to 1.0 typically from Controller (Player or AI) input.
	void ModifyEngineImpulse(float Rate);
	
};
