/*
This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
Attribution-NonCommercial-ShareAlike 4.0 International
An EscapeVelocity Production (Nate Gillard).
*/

#pragma once

#include "ShipPawn.h"
#include "PlayerShip.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class FPDEV_API APlayerShip : public AShipPawn
{
	GENERATED_BODY()

public:

	APlayerShip();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE class UCameraComponent* GetCameraComponent() const { return BoomCamera; }

	FORCEINLINE class USpringArmComponent* GetCameraSpringArm() const { return BoomArm; }

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//initialize the pawn's mesh and other viewable components
	virtual void SetupPawnView() override;

	//Return the mesh component(s) used for this pawn.
	virtual UStaticMeshComponent* GetPawnUsedView() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* BoomCamera;

	UPROPERTY(VisibleAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* BoomArm;

};
