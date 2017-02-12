// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MortalInterface.h"
#include "MortalActor.generated.h"

UCLASS()
class FPDEV_API AMortalActor : public AActor, public IMortalInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMortalActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//Remaining health (basic implentation)
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category= "Health System") int32 Health;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Health System")
		bool IsHealthDepleated() const;
	virtual bool IsHealthDepleated_Implementation() const override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Health System")
		void HealthDepleated();
	virtual void HealthDepleated_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Damage")
		float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser);
	virtual float TakeDamage_Implementation(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;
};
