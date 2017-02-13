// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "FPDev.h"
#include "FPDevCharacter.h"
#include "FPDevProjectile.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/HeadMountedDisplayFunctionLibrary.h"
#include "MotionControllerComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AFPDevCharacter

AFPDevCharacter::AFPDevCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);

	// Create a gun mesh component
	//FP_Gun = CreateDefaultSubobject<UWeaponComponent>(TEXT("FP_Gun"));
	//FP_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	//FP_Gun->bCastDynamicShadow = false;
	//FP_Gun->CastShadow = false;
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	//FP_Gun->SetupAttachment(RootComponent);

	//FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	//FP_MuzzleLocation->SetupAttachment(FP_Gun);
	//FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P, and FP_Gun
	// are set in the derived blueprint asset named MyCharacter to avoid direct content references in C++.
	
	Health = 100.0f;
}

void AFPDevCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	//FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	WeaponFunction = NewObject<UWeaponMechanic>();
	
	TimeSinceFire = 0.0f;

	FireQueue.Init(true, 0);
	TimeSinceBulletSpawn = 0.0f;

	
	Mesh1P->SetHiddenInGame(false, true);

}

//////////////////////////////////////////////////////////////////////////
// Input

void AFPDevCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	//InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AFPDevCharacter::TouchStarted);
	if (EnableTouchscreenMovement(PlayerInputComponent) == false)
	{
		PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPDevCharacter::OnFire);
	}

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

void AFPDevCharacter::OnFire()
{
	// try and fire a projectile
	if (FP_Gun != NULL)
	{
		if (!(TimeSinceFire < WeaponFunction->FireDelay)) {
			for (int32 i = 0; i < WeaponFunction->ShotMultiplier; ++i) {
				FireQueue.Add(true);
			}
			
		}
	
	}

	
}

void AFPDevCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AFPDevCharacter::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == true)
	{
		return;
	}
	TouchItem.bIsPressed = true;
	TouchItem.FingerIndex = FingerIndex;
	TouchItem.Location = Location;
	TouchItem.bMoved = false;
}

void AFPDevCharacter::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == false)
	{
		return;
	}
	if ((FingerIndex == TouchItem.FingerIndex) && (TouchItem.bMoved == false))
	{
		OnFire();
	}
	TouchItem.bIsPressed = false;
}

//Commenting this section out to be consistent with FPS BP template.
//This allows the user to turn without using the right virtual joystick

//void AFPDevCharacter::TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location)
//{
//	if ((TouchItem.bIsPressed == true) && (TouchItem.FingerIndex == FingerIndex))
//	{
//		if (TouchItem.bIsPressed)
//		{
//			if (GetWorld() != nullptr)
//			{
//				UGameViewportClient* ViewportClient = GetWorld()->GetGameViewport();
//				if (ViewportClient != nullptr)
//				{
//					FVector MoveDelta = Location - TouchItem.Location;
//					FVector2D ScreenSize;
//					ViewportClient->GetViewportSize(ScreenSize);
//					FVector2D ScaledDelta = FVector2D(MoveDelta.X, MoveDelta.Y) / ScreenSize;
//					if (FMath::Abs(ScaledDelta.X) >= 4.0 / ScreenSize.X)
//					{
//						TouchItem.bMoved = true;
//						float Value = ScaledDelta.X * BaseTurnRate;
//						AddControllerYawInput(Value);
//					}
//					if (FMath::Abs(ScaledDelta.Y) >= 4.0 / ScreenSize.Y)
//					{
//						TouchItem.bMoved = true;
//						float Value = ScaledDelta.Y * BaseTurnRate;
//						AddControllerPitchInput(Value);
//					}
//					TouchItem.Location = Location;
//				}
//				TouchItem.Location = Location;
//			}
//		}
//	}
//}

void AFPDevCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AFPDevCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AFPDevCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AFPDevCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

bool AFPDevCharacter::EnableTouchscreenMovement(class UInputComponent* PlayerInputComponent)
{
	bool bResult = false;
	if (FPlatformMisc::GetUseVirtualJoysticks() || GetDefault<UInputSettings>()->bUseMouseForTouch)
	{
		bResult = true;
		PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AFPDevCharacter::BeginTouch);
		PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &AFPDevCharacter::EndTouch);

		//Commenting this out to be more consistent with FPS BP template.
		//PlayerInputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AFPDevCharacter::TouchUpdate);
	}
	return bResult;
}

void AFPDevCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsHealthDepleated()) {
		HealthDepleated();
	}

	if (FireQueue.Num() > 0 && !(TimeSinceBulletSpawn < WeaponFunction->MultiplierDelay) ) {
		const FRotator SpawnRotation = GetControlRotation();

		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
		const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(FVector(100.0f, 0.0f, 5.0f));
		//const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(FP_Gun->GunOffset);
		
		if (ProjectileClass != NULL) {

			UWorld* const World = GetWorld();

			if (World != NULL)
			{

				if (FP_Gun != NULL) {
					// try and play the sound if specified
					if (FP_Gun->FireSound != NULL)
					{
						UGameplayStatics::PlaySoundAtLocation(this, FP_Gun->FireSound, GetActorLocation());
					}

					// try and play a firing animation if specified
					if (FP_Gun->FireAnimation != NULL)
					{
						// Get the animation object for the arms mesh
						UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
						if (AnimInstance != NULL)
						{
							AnimInstance->Montage_Play(FP_Gun->FireAnimation, 1.f);
						}
					}
				}
				//Set Spawn Collision Handling Override
				FActorSpawnParameters ActorSpawnParams;
				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

				// spawn the projectile at the muzzle

				int32 i = 0;
				for (auto& cell : WeaponFunction->SpreadPattern) {
					if (cell) {
						float x = i%WeaponFunction->SpreadWidth - (float(WeaponFunction->SpreadWidth) / 2.0f);
						float y = (i / WeaponFunction->SpreadWidth - (WeaponFunction->GetSpreadHeight() / 2.0f));
						FVector p = FVector(SpawnLocation.X, SpawnLocation.Y, SpawnLocation.Z);
						p -= WeaponFunction->SpreadDepth * UKismetMathLibrary::GetForwardVector(SpawnRotation);
						p += y * WeaponFunction->GetSpreadCellHeight() * UKismetMathLibrary::GetUpVector(SpawnRotation);
						p += x * WeaponFunction->GetSpreadCellWidth() * UKismetMathLibrary::GetRightVector(SpawnRotation);

						/*FVector s = FVector(SpawnLocation.X, SpawnLocation.Y, SpawnLocation.Z);
						s += y * 15 * UKismetMathLibrary::GetUpVector(SpawnRotation);
						s += x * 15 * UKismetMathLibrary::GetRightVector(SpawnRotation);*/

						p = SpawnLocation - p;

						p.Normalize();

						World->SpawnActor<AFPDevProjectile>(ProjectileClass,
							SpawnLocation,
							p.ToOrientationRotator(), ActorSpawnParams);
					}

					++i;
				}

				

				FireQueue.RemoveAt(0);
				TimeSinceBulletSpawn = 0.0f;
			}
		}
	}
	else {
		TimeSinceBulletSpawn += DeltaTime;
		TimeSinceFire += DeltaTime;
	}
}

bool AFPDevCharacter::AttachWeapon(UClass* CompClass)
{
	//CompClass can be a BP
	FP_Gun = NewObject<UWeaponComponent>(this, CompClass);
	if (!FP_Gun)
	{
		return false;
	}

	FP_Gun->RegisterComponent();			//You must ConstructObject with a valid Outer that has world, see above	 
	FP_Gun->AttachTo(RootComponent, NAME_None, EAttachLocation::SnapToTarget);
	FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	FP_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;

	FP_MuzzleLocation = NewNamedObject<USceneComponent>(this, TEXT("MuzzleLocation"));
	FP_MuzzleLocation->RegisterComponent();
	FP_MuzzleLocation->AttachTo(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	return true;
}

bool AFPDevCharacter::IsHealthDepleated_Implementation() const {
	return !(Health > 0.0);
}

void AFPDevCharacter::HealthDepleated_Implementation() {
	Destroy();
}

float AFPDevCharacter::TakeDamage_Implementation(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) {
	Health -= DamageAmount;

	return DamageAmount;
}