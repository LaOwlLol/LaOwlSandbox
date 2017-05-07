/*
This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
Attribution-NonCommercial-ShareAlike 4.0 International
LaOwlSandbox
An EscapeVelocity Production (Nate Gillard).
*/

#pragma once

#include "GameFramework/Actor.h"
#include "WeaponEntity.generated.h"

UCLASS(Blueprintable, BlueprintType)
class LAOWLSANDBOX_API AWeaponEntity : public AActor
{
	/* Private Members */

	/* Private Methods */

	GENERATED_BODY()

protected:

	/*Protected  Members */

	/*Protected  Methods */

	// Called when the game starts
	virtual void BeginPlay() override;

public:

	/* Public Members */

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* WeaponBody;

	/**
	Location on gun mesh where "the action should happen".
	For a fireaarm type weapon this is where projectile will spawn. IE the muzzle or barrel end.
	Designers should move this point using Component Editor to the end ot the skeletalMesh barrel.
	**/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Mesh)
		class USceneComponent* ActivationPoint;

	/** Sound to play each time we fire */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* ActivationSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gameplay)
		class UAnimMontage* ActivationAnimation;

	/* Public Methods */

	// Sets default values for this actor's properties
	AWeaponEntity();

	//check if the weapon has a sound to play on activation.
	bool HasActivationPoint() const { return ActivationPoint != nullptr; }

	//return the activation sound.
	class USceneComponent* GetActivationPoint() const { return ActivationPoint; }

	//check if the weapon has a sound to play on activation.
	bool HasActivationSound() const { return ActivationSound != nullptr; }

	//return the activation sound.
	class USoundBase* GetActivationSound() const { return ActivationSound; }

	//Check if the weapon has an animation to play on activation. 
	bool HasActivationAnimation() const { return ActivationAnimation != nullptr; }

	//Return the ActivationAnitmation.
	class UAnimMontage* GetActivationAnimation() const { return ActivationAnimation; }
	
};
