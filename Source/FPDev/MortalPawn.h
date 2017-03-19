// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "MortalInterface.h"
#include "MortalPawn.generated.h"

UCLASS(Blueprintable)
class FPDEV_API AMortalPawn : public APawn, public IMortalInterface
{
	GENERATED_BODY()

public:

	// Sets default values for this pawn's properties
	AMortalPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Remaining health (basic implentation)
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Health System") int32 Health;

	//Check if health is remaining
	//Default: false if health > 0.0 
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Health System")
		bool IsHealthDepleated() const;
	virtual bool IsHealthDepleated_Implementation() const override;

	//Event called when IsHealthDepleated is true.
	//Default: destroy this character.
	//Recommended to always end by destroy this character.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Health System")
		void HealthDepleated();
	virtual void HealthDepleated_Implementation() override;

	//Apply damage.
	//Default: Health -= DamageAmount.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Damage")
		float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser);
	virtual float TakeDamage_Implementation(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//initialize the pawn's mesh and other viewable components
	virtual void SetupPawnView();

	//Return the mesh component(s) used for this pawn.
	virtual UStaticMeshComponent* GetPawnUsedView();

	UPROPERTY(EditAnyWhere, Category = Mesh)
		UStaticMeshComponent* BodyMesh;

};
