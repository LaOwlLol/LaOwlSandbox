/*
This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
Attribution-NonCommercial-ShareAlike 4.0 International
LaOwlSandbox
An EscapeVelocity Production (Nate Gillard).
*/

#pragma once

#include "ArmedCharacter.h"
#include "HumanoidCharacter.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class LAOWLSANDBOX_API AHumanoidCharacter : public AArmedCharacter
{
	/* Private Members */

	/* Private Methods */

	GENERATED_BODY()
	
protected:

	/*Protected  Members */
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	/*Protected  Methods */

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	

public:

	/* Public Members */

	/* Public Methods */

	AHumanoidCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void MoveForward(float Value);

	void MoveRight(float Value);

	void TurnAtRate(float Rate);
	
	void LookUpAtRate(float Rate);
	
};
