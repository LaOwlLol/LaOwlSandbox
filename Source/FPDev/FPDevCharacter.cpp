// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "FPDev.h"
#include "FPDevCharacter.h"

#include "GameFramework/InputSettings.h"
#include "Kismet/HeadMountedDisplayFunctionLibrary.h"
#include "MotionControllerComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AFPDevCharacter

AFPDevCharacter::AFPDevCharacter() : Super()
{
	
	SetUpFirstPersonView();
	// Create a gun mesh component
	//WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("FP_Gun"));
	//WeaponComponent->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	//WeaponComponent->bCastDynamicShadow = false;
	//WeaponComponent->CastShadow = false;
	//WeaponComponent->SetupAttachment(FirstPersonMesh, TEXT("GripPoint"));
	//WeaponComponent->SetupAttachment(RootComponent);

	//FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	//FP_MuzzleLocation->SetupAttachment(WeaponComponent);
	//FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for FirstPersonMesh, and WeaponComponent
	// are set in the derived blueprint asset named MyCharacter to avoid direct content references in C++.
	
}

void AFPDevCharacter::SetUpFirstPersonView() {
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->SetupAttachment(GetFirstPersonCameraComponent());
	FirstPersonMesh->bCastDynamicShadow = false;
	FirstPersonMesh->CastShadow = false;
	FirstPersonMesh->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	FirstPersonMesh->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);
}

void AFPDevCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	FirstPersonMesh->SetHiddenInGame(false, true);

}

// Setup Input bindings
void AFPDevCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPDevCharacter::OnFire);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPDevCharacter::ToggleTrigger);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AFPDevCharacter::ToggleTrigger);
	


	PlayerInputComponent->BindAxis("MoveForward", this, &AFPDevCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPDevCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AFPDevCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AFPDevCharacter::LookUpAtRate);
}

void AFPDevCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}