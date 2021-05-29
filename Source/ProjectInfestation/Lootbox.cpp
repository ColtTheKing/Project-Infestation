// Fill out your copyright notice in the Description page of Project Settings.


#include "Lootbox.h"

ALootbox::ALootbox()
{

}

void ALootbox::BeginPlay()
{
	Super::BeginPlay();

	// Get reference to spawn area
	spawnArea = Cast<UBoxComponent>(GetDefaultSubobjectByName(TEXT("SpawnArea")));
	opened = false;
}

void ALootbox::SpawnLoot() 
{
	// Check if opened
	if (opened)
		return;

	opened = true;

	if (!(FGenericPlatformMath::FRand() < healthSpawnChance))
		return;

	// Calculate bounding box
	FTransform localToWorld = FTransform(spawnArea->GetComponentLocation());
	FBox boundingBox = FBox::BuildAABB(localToWorld.GetLocation(), spawnArea->GetScaledBoxExtent());

	// Calculate random location in bounding box
	FVector randomLocation;
	randomLocation = boundingBox.Min;
	randomLocation.X += FGenericPlatformMath::FRand() * (boundingBox.Max.X - boundingBox.Min.X);
	randomLocation.Y += FGenericPlatformMath::FRand() * (boundingBox.Max.Y - boundingBox.Min.Y);
	randomLocation.Z += (boundingBox.Max.Z - boundingBox.Min.Z);

	// Spawn a enemy
	FRotator spawnRotation = FRotator(0.0f, 0.0f, 0.0f);
	AActor* spawnedEnemy = GetWorld()->SpawnActor(healthBP, &randomLocation, &spawnRotation);

}
