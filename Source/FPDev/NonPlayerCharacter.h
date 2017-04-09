/*
This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
Attribution-NonCommercial-ShareAlike 4.0 International
An EscapeVelocity Production (Nate Gillard).
*/

#pragma once

#include "GameFramework/Character.h"
#include "MortalCharacter.h"
#include "NonPlayerCharacter.generated.h"

UCLASS(Blueprintable)
class FPDEV_API ANonPlayerCharacter : public AMortalCharacter
{
	GENERATED_BODY()

	USkeletalMeshComponent* UsedMesh;

protected:

	virtual void SetupCharacterView() override;

	virtual class USkeletalMeshComponent* GetCharaterUsedMesh() override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this character's properties
	ANonPlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	//Attach a weaponComponent of CompClass to
	//Each derived class implements this method to attach weapon.
	UFUNCTION(BlueprintCallable, Category = "Weapon")
		virtual bool AttachWeapon(UClass* ComponentClass) override;

	UPROPERTY(EditAnyWhere, Category = Pawn)
	class UBehaviorTree* BehaviorTree;
};
