// Fill out your copyright notice in the Description page of Project Settings.

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* BoomCamera;

	UPROPERTY(VisibleAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* BoomArm;

};
