/*
This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
Attribution-NonCommercial-ShareAlike 4.0 International
An EscapeVelocity Production (Nate Gillard).
*/

#include "FPDev.h"
#include "WeaponComponent.h"
#include "NonPlayerCharacter.h"


// Sets default values
ANonPlayerCharacter::ANonPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetupCharacterView();

	GetMovementComponent()->NavAgentProps.AgentHeight = 320.0f;
	GetMovementComponent()->NavAgentProps.AgentRadius = 160.0f;

}

void ANonPlayerCharacter::SetupCharacterView()
{
	//grab the mesh from character base class.
	UsedMesh = GetMesh();
}

USkeletalMeshComponent * ANonPlayerCharacter::GetCharaterUsedMesh()
{
	return UsedMesh;
}

// Called when the game starts or when spawned
void ANonPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANonPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ANonPlayerCharacter::AttachWeapon(UClass* ComponentClass)
{
	//CompClass can be a BP
	WeaponComponent = NewObject<UWeaponComponent>(this, ComponentClass);
	if (!WeaponComponent)
	{
		return false;
	}

	WeaponComponent->RegisterComponent();			//You must ConstructObject with a valid Outer that has world, see above	 
	//WeaponComponent->AttachTo(GetCharaterUsedMesh(), NAME_None, EAttachLocation::SnapToTarget);
	WeaponComponent->AttachToComponent(GetCharaterUsedMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	WeaponComponent->bCastDynamicShadow = true;
	WeaponComponent->CastShadow = true;

	FP_MuzzleLocation = NewObject<USceneComponent>(this, TEXT("MuzzleLocation"));
	FP_MuzzleLocation->RegisterComponent();
	FP_MuzzleLocation->AttachTo(WeaponComponent);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, 10.6f));

	return true;
}
