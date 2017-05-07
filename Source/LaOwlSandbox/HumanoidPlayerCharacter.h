/*
This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
Attribution-NonCommercial-ShareAlike 4.0 International
LaOwlSandbox
An EscapeVelocity Production (Nate Gillard).
*/

#pragma once

#include "HumanoidCharacter.h"
#include "HumanoidPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class LAOWLSANDBOX_API AHumanoidPlayerCharacter : public AHumanoidCharacter
{
	/* Private Members */

	/* Private Methods */

	GENERATED_BODY()

protected:

	/*Protected  Members */

	/*Protected  Methods */

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Setup Player controls for humanoid
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

public:

	/* Public Members */

	/* Public Methods */

	AHumanoidPlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
