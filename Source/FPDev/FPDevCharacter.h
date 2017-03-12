// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "MortalCharacter.h"
#include "FPDevCharacter.generated.h"

class UInputComponent;

UCLASS(Blueprintable)
class AFPDevCharacter : public AMortalCharacter
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;

	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	AFPDevCharacter();

	// Called every frame
	virtual void Tick(float DeltaSeconds);

};

