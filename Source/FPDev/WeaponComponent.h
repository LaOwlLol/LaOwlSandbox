/*
This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
Attribution-NonCommercial-ShareAlike 4.0 International
An EscapeVelocity Production (Nate Gillard).
*/

#pragma once

#include "Components/SkeletalMeshComponent.h"
#include "WeaponInterface.h"
#include "WeaponComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class FPDEV_API UWeaponComponent : public USkeletalMeshComponent, public IWeaponInterface
{
	GENERATED_BODY()
	
public:

	UWeaponComponent();
	
	/** Sound to play each time we fire */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* ActivationSound;

	//check if the weapon has a sound to play on activation.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Gameplay)
		bool HasActivationSound() const;
	virtual bool HasActivationSound_Implementation() const { return ActivationSound != NULL; }

	//return the activation sound.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Gameplay)
		class USoundBase* GetActivationSound() const;
	virtual class USoundBase* GetActivationSound_Implementation() const;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* ActivationAnimation;

	//Check if the weapon has an animation to play on activation. 
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Gameplay)
		bool HasActivationAnimation() const;
	virtual bool HasActivationAnimation_Implementation() const { return ActivationAnimation != NULL; }

	//Return the ActivationAnitmation.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Gameplay)
		class UAnimMontage* GetActivationAnimation() const;
	virtual class UAnimMontage* GetActivationAnimation_Implementation() const;

};
