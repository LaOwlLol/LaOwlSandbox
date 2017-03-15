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

	//First person camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	//First person view mesh
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FirstPersonMesh;
	
protected:

	virtual class USkeletalMeshComponent* GetCharaterUsedMesh() override;

	virtual void SetupCharacterView() override;

	virtual void BeginPlay() override;

	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	AFPDevCharacter();

	// Called every frame
	virtual void Tick(float DeltaSeconds);

	//Attach a weaponComponent of CompClass to
	//Each derived class implements this method to attach weapon.
	UFUNCTION(BlueprintCallable, Category = "Weapon")
		virtual bool AttachWeapon(UClass* ComponentClass) override;

	//Returns FirstPersonCameraComponent subobject
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }	
	//Returns FirstPersonMesh subobject
	FORCEINLINE class USkeletalMeshComponent* GetFirstPersonMesh() const { return FirstPersonMesh; }
};

