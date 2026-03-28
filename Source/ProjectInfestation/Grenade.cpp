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
	FRotator grenadeRotation = spawnPosition->GetComponentRotation();
	TWeakObjectPtr<AActor> spawnedGrenade = Cast<AActor>(GetWorld()->SpawnActor(heldGrenade.grenadeBP, &grenadeLocation, &grenadeRotation));
	
	// Add impluse
	if (spawnedGrenade != nullptr) 
	{
		UPrimitiveComponent* comp = Cast<UPrimitiveComponent>(spawnedGrenade->FindComponentByClass<UPrimitiveComponent>());
		comp->AddImpulse(GetActorForwardVector() * throwStrength, FName("None"), true);
	}
} 

