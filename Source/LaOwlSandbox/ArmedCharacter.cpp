/*
This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
Attribution-NonCommercial-ShareAlike 4.0 International
LaOwlSandbox
An EscapeVelocity Production (Nate Gillard).
*/

#include "LaOwlSandbox.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "WeaponMechanicComponent.h"
#include "WeaponEntity.h"
#include "Projectile.h"
#include "ArmedCharacter.h"

AArmedCharacter::AArmedCharacter(const FObjectInitializer& ObjectInitializer)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AArmedCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetupWeaponMechanic();

	TimeSinceFire = 0.0f;
	FireQueue.Init(true, 0);
	TimeSinceBulletSpawn = 0.0f;
	TriggerHeld = false;
}

void AArmedCharacter::SetupWeaponMechanic()
{
	if (WeaponMechanicType) {
		//conststruct the type selected.  
		WeaponMechanic = NewObject<UWeaponMechanicComponent>(this, GetUsedWeaponMechanicType(), TEXT("WeaponMechanic"));
	}
	else {
		//construct a default weapon mechanic.
		WeaponMechanic = NewObject<UWeaponMechanicComponent>(this, TEXT("WeaponMechanic"));
	}

	if (WeaponMechanic) {
		WeaponMechanic->RegisterComponent();
	}
}

UClass * AArmedCharacter::GetUsedWeaponMechanicType()
{
	return WeaponMechanicType;
}

void AArmedCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FireWeapon(DeltaTime);

	if (TriggerHeld && WeaponMechanic->FullAutomatic) {
		OnFire();
	}
}

bool AArmedCharacter::AttachWeapon(UClass * WeaponClass)
{

		 
	if (WeaponEntity) {
		WeaponEntity->DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
		//WeaponEntity->WeaponBody->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true) );
		//WeaponEntity->WeaponBody->UnregisterComponent();			//You must ConstructObject with a valid Outer that has world, see above
	}

	WeaponEntity = NewObject<AWeaponEntity>(this, WeaponClass, TEXT("Weapon"));

	if (!WeaponEntity) {
		return false;
	}
	else {
		
	}

	//WeaponEntity->WeaponBody->RegisterComponent();
	//WeaponEntity->WeaponBody->AttachTo(RootComponent, NAME_None, EAttachLocation::SnapToTarget);
	//WeaponEntity->WeaponBody->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));

	//WeaponEntity->AttachRootComponentToActor(this, TEXT("GripPoint"), EAttachLocation::SnapToTarget, true);
	WeaponEntity->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));

	return true;
	
}

void AArmedCharacter::OnFire()
{
	ActivateWeapon();
}

bool AArmedCharacter::ActivateWeapon()
{
	if (WeaponMechanic) {
		if (TimeSinceFire > WeaponMechanic->FireDelay) {
			for (int32 i = 0; i < WeaponMechanic->ShotMultiplier; ++i) {
				FireQueue.Add(true);
			}
			TimeSinceFire = 0.0;
			return true;
		}
	}
	return false;
}

void AArmedCharacter::FireWeapon(float DeltaTime)
{
	if (FireQueue.Num() > 0 && TimeSinceBulletSpawn > WeaponMechanic->MultiplierDelay) {
		const FRotator SpawnRotation = GetControlRotation();

		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
		FVector SpawnLocation;
		if (WeaponEntity) {
			if (WeaponEntity->HasActivationPoint()) {
				SpawnLocation = WeaponEntity->GetActivationPoint()->GetComponentLocation();
			}
				
		}
		else {
			SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(FVector(200.0f, 0.0f, 0.0f));
		}

		//TODO: NExT Line! in if above plus chack and get for activation point.
		//const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(WeaponEntity->GunOffset);

		if (ProjectileClass != NULL) {

			UWorld* const World = GetWorld();

			if (World != NULL)
			{

				//do sound and animation.
				if (WeaponEntity) {
					// try and play the sound if specified
					if (WeaponEntity->HasActivationSound())
					{
						UGameplayStatics::PlaySoundAtLocation(this, WeaponEntity->GetActivationSound(), GetActorLocation());
					}
					if (WeaponEntity->HasActivationAnimation())
					{
						// Get the animation object for the arms mesh
						UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
						if (AnimInstance != NULL)
						{
							AnimInstance->Montage_Play(WeaponEntity->GetActivationAnimation(), 1.f);
						}
					}
				}
	

				//Set Spawn Collision Handling Override
				FActorSpawnParameters ActorSpawnParams;
				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;


				float cellDim = WeaponMechanic->GetSpreadCellDim();
				float offSetW = (float(WeaponMechanic->SpreadWidth) / 2.0f);
				float offSetH = (float(WeaponMechanic->GetSpreadHeight()) / 2.0f);
				FVector Forward = UKismetMathLibrary::GetForwardVector(SpawnRotation);
				FVector Up = UKismetMathLibrary::GetUpVector(SpawnRotation);
				FVector Right = UKismetMathLibrary::GetRightVector(SpawnRotation);
				FVector Dist = WeaponMechanic->SpreadDepth * Forward;
				//FVector inheritedVelocity = Forward * ImpulseEngine->GetEngineImpulse();
				int32 i = 0;
				//for each element or cell in the SpreadPattern array.
				for (auto& cell : WeaponMechanic->SpreadPattern) {
					if (cell) {
						//transform Pattern index to x and y coordinates
						float x = (i % WeaponMechanic->SpreadWidth) - offSetW;
						float y = (i / WeaponMechanic->SpreadWidth) - offSetH;

						//use x, y, and SpreadDepth to transform the projectile's spawn point to the projectile's target point.
						FVector p = FVector(SpawnLocation.X, SpawnLocation.Y, SpawnLocation.Z);
						p += Dist;
						p += ((y * cellDim) + (0.5f * cellDim)) * Up;
						p += ((x * cellDim) + (0.5f * cellDim)) * Right;

						//get the direction vector normalized.
						p = p - SpawnLocation;
						p.Normalize();

						//spawn a projectile at the weapon barrel which is rotated to point at it's SpreadPattern target point.
						
						AProjectile* projectile = World->SpawnActor<AProjectile>(ProjectileClass,
							SpawnLocation,
							p.ToOrientationRotator(), ActorSpawnParams);
						if (projectile) {
							//projectile->AddVelocity(inheritedVelocity);
						}
						
					}

					//next cell.
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

/*
// Called to bind functionality to input
void AMortalCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
Super::SetupPlayerInputComponent(PlayerInputComponent);

}
*/
