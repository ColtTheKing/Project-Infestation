// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"

#include "Math/BoxSphereBounds.h"
#include "GenericPlatform/GenericPlatformMath.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
	// Get reference to spawn area
	spawnArea = FindComponentByClass<UBoxComponent>();

	// Spawn enemies
	for (auto& enemy : enemies)
	{
		int i = 0;
		while (i < enemy.spawn_limit)
		{
			SpawnEnemy(enemy.enemyCharacterBP);
			i++;
		}
	}

	// Respawn test
	FName enemyToRespawnTag = FName(TEXT("Swarmer"));
	RespawnEnemy(enemyToRespawnTag);
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemySpawner::SpawnEnemy(TSubclassOf<AEnemyCharacter> enemyBP)
{
	// Calculate bounding box
	FTransform localToWorld = FTransform(GetActorLocation());
	FBoxSphereBounds spawnBounds = spawnArea->CalcBounds(localToWorld);
	FBox boundingBox = spawnBounds.GetBox();

	// Calculate random location in bounding box
	FVector randomLocation;
	randomLocation = boundingBox.Min;
	randomLocation.X += FGenericPlatformMath::FRand() * (boundingBox.Max.X - boundingBox.Min.X);
	randomLocation.Y += FGenericPlatformMath::FRand() * (boundingBox.Max.Y - boundingBox.Min.Y);
	randomLocation.Z += FGenericPlatformMath::FRand() * (boundingBox.Max.Z - boundingBox.Min.Z);

	// Spawn a enemy
	FRotator spawnRotation = FRotator(0.0f, 0.0f, 0.0f);
	GetWorld()->SpawnActor(enemyBP, &randomLocation, &spawnRotation);
}


void AEnemySpawner::RespawnEnemy(FName enemyTag)
{
	FEnemy enemyToSpawn;
	bool foundEnemyTag = false;
	for (auto& enemy : enemies)
	{
		if (enemy.enemyCharacterBP.GetDefaultObject()->ActorHasTag(enemyTag))
		{
			enemyToSpawn = enemy;
			foundEnemyTag = true;
			break;
		}
	}

	if (!foundEnemyTag) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Unable to find enemy of tag %s"), *enemyTag.ToString());
		return;
	}
}
