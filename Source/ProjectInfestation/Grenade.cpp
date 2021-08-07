// Fill out your copyright notice in the Description page of Project Settings.

#include "Grenade.h"

AGrenade::AGrenade() : Super()
{

}

void AGrenade::BeginPlay() 
{
	Super::BeginPlay();

	// Setup weapon mesh with held grenade
	weaponMesh->SetStaticMesh(heldGrenade.grenadeMesh);
	weaponMesh->SetWorldScale3D(heldGrenade.meshScale);
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
	FVector grenadeLocation = GetActorLocation();
	FRotator grenadeRotation = FRotator(0.0f, 0.0f, 0.0f);
	TWeakObjectPtr<AActor> spawnedGrenade = Cast<AActor>(GetWorld()->SpawnActor(heldGrenade.grenadeBP, &grenadeLocation, &grenadeRotation));
	
	// Add impluse
	if (spawnedGrenade != nullptr) 
	{
		UPrimitiveComponent* comp = Cast<UPrimitiveComponent>(spawnedGrenade->FindComponentByClass<UPrimitiveComponent>());
		comp->AddImpulse(GetActorForwardVector() * throwStrength, FName("None"), true);
	}
}
