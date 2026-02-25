// Fill out your copyright notice in the Description page of Project Settings.

#include "Grenade.h"

AGrenade::AGrenade() : Super()
{
	// Add a mesh for where the grenade's will be spawned
	spawnPosition = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Grenade Spawn Position"));
	spawnPosition->SetupAttachment(weaponMesh);
	spawnPosition->SetVisibility(false);
}

void AGrenade::BeginPlay() 
{
	Super::BeginPlay();

	// Setup weapon mesh with held grenade
	// Note: Unsure what this did, it's possible it worked before the arsenal system was updated 
	//       but now it just breaks stuff.
	// weaponMesh->SetStaticMesh(heldGrenade.grenadeMesh);
	// weaponMesh->SetWorldScale3D(heldGrenade.meshScale);
}

void AGrenade::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
}

void AGrenade::ConsumeAmmo(int ammo) 
{
	if (ammoInClip >= ammo)
		ammoInClip -= ammo;
}

void AGrenade::ThrowGrenade() 
{
	// Spawn Grenade
	FVector grenadeLocation = spawnPosition->GetComponentLocation();
	FRotator grenadeRotation = FRotator::ZeroRotator;
	TWeakObjectPtr<AActor> spawnedGrenade = Cast<AActor>(GetWorld()->SpawnActor(heldGrenade.grenadeBP, &grenadeLocation, &grenadeRotation));
	
	// Add impluse
	if (spawnedGrenade != nullptr) 
	{
		UPrimitiveComponent* comp = Cast<UPrimitiveComponent>(spawnedGrenade->FindComponentByClass<UPrimitiveComponent>());
		comp->AddImpulse(GetActorForwardVector() * throwStrength, FName("None"), true);
	}
}
