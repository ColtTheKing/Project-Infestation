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

	// Spawn Loot
	for (auto& loot : loots)
	{
		unsigned int i = 0;
		while (i < loot.spawnLimit)
		{
			if (!(FGenericPlatformMath::FRand() < loot.spawnChance))
				break;
			
			// Calculate bounding box
			FTransform localToWorld = FTransform(spawnArea->GetComponentLocation());
			FBox boundingBox = FBox::BuildAABB(localToWorld.GetLocation(), spawnArea->GetScaledBoxExtent());

			// Calculate random location in bounding box
			FVector randomLocation;
			randomLocation = boundingBox.Min;
			randomLocation.X += FGenericPlatformMath::FRand() * (boundingBox.Max.X - boundingBox.Min.X);
			randomLocation.Y += FGenericPlatformMath::FRand() * (boundingBox.Max.Y - boundingBox.Min.Y);
			randomLocation.Z += (boundingBox.Max.Z - boundingBox.Min.Z);

			// Spawn loot
			FRotator spawnRotation = FRotator(0.0f, 0.0f, 0.0f);
			GetWorld()->SpawnActor(loot.lootBP, &randomLocation, &spawnRotation);

			i++;
		}
	}
}
