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
	
	// Init variables
	spawnArea = FindComponentByClass<UBoxComponent>();
	enemiesSpawned = 0;
	respawnTimer = respawnRate;

	// Spawn enemies
	for (int i = 0; i < spawnLimit; i++)
		SpawnEnemy();
}

// Called every frame
void AEnemySpawner::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	respawnTimer -= deltaTime;
	if (enemiesSpawned < spawnLimit && respawnTimer <= 0)
		SpawnEnemy();
}

void AEnemySpawner::SpawnEnemy()
{
	TSubclassOf<AEnemyCharacter> enemy = GetRandomEnemy();
	if (enemy == nullptr)
		return;

	// Calculate bounding box
	FTransform localToWorld = FTransform(GetActorLocation());
	FBox boundingBox = FBox::BuildAABB(localToWorld.GetLocation(), spawnArea->GetScaledBoxExtent());

	// Calculate random location in bounding box
	FVector randomLocation;
	randomLocation = boundingBox.Min;
	randomLocation.X += FGenericPlatformMath::FRand() * (boundingBox.Max.X - boundingBox.Min.X);
	randomLocation.Y += FGenericPlatformMath::FRand() * (boundingBox.Max.Y - boundingBox.Min.Y);
	randomLocation.Z += FGenericPlatformMath::FRand() * (boundingBox.Max.Z - boundingBox.Min.Z);

	// Spawn a enemy
	FRotator spawnRotation = FRotator(0.0f, 0.0f, 0.0f);
	
	CreateEnemyActor(enemy, randomLocation, spawnRotation);
	enemiesSpawned++;
	respawnTimer = respawnRate;
	
	/*TWeakObjectPtr<ABasicEnemy> spawnedEnemy = Cast<ABasicEnemy>(GetWorld()->SpawnActor(enemy, &randomLocation, &spawnRotation));

	if (spawnedEnemy != nullptr)
		spawnedEnemy->SetEnemySpawner(this);
	}*/
}

TSubclassOf<AEnemyCharacter> AEnemySpawner::GetRandomEnemy()
{
	float count = 0;
	float randNum = FGenericPlatformMath::FRand();
	for (auto& enemy : enemies)
	{
		count += enemy.respawnChance;
		if (enemy.respawnChance != 0 && randNum <= enemy.respawnChance)
		{
			return enemy.enemyCharacterBP;
		}
	}
	return nullptr;
}

void AEnemySpawner::HandleEnemyDespawn()
{
	if (enemiesSpawned - 1 <= 0) 
		return;

	if (enemiesSpawned < spawnLimit)
		respawnTimer = respawnRate;
	
	enemiesSpawned--;
}
