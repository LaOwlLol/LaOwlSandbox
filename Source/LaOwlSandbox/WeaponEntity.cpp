/*
This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
Attribution-NonCommercial-ShareAlike 4.0 International
LaOwlSandbox
An EscapeVelocity Production (Nate Gillard).
*/

#include "LaOwlSandbox.h"
#include "WeaponEntity.h"


// Sets default values
AWeaponEntity::AWeaponEntity()
{
	WeaponBody = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponBody"));
	WeaponBody->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));

	ActivationPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ActivationPoint"));
	ActivationPoint->AttachToComponent(WeaponBody, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("Muzzle") );

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AWeaponEntity::BeginPlay()
{
	Super::BeginPlay();
	WeaponBody->SetVisibility(true, true);
}