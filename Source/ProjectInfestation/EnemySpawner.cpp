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
	enemiesSpawned = 0;
	respawnTimer = respawnRate;

	// Setup spawn points
	for (int i = 0; i < spawnLocations.Num(); i++)
	{
		FVector spawnPosition = spawnLocations[i].positioner;
		FRotator spawnRotation = FRotator(0.0f, 0.0f, 0.0f);
		AActor* pointActor = GetWorld()->SpawnActor(spawnLocations[i].spawnPointBP, &spawnPosition, &spawnRotation);
		spawnPoints.Add((ASpawnPoint*)pointActor);
	}

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
	if (enemy == nullptr || spawnPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot spawn as enemy or spawn point is null"));
		return;
	}

	//Get a random spawn point
	int ind = FGenericPlatformMath::FRand() * spawnPoints.Num();
	FTransform localToWorld = FTransform(spawnPoints[ind]->GetActorLocation());
	FVector spawnLocation = GetTransform().TransformPosition(spawnPoints[ind]->GetActorLocation());

	//Spawn the enemy at that point
	FRotator spawnRotation = FRotator(0.0f, 0.0f, 0.0f);
	CreateEnemyActor(enemy, spawnLocation, spawnRotation);
	spawnPoints[ind]->SpawnEnemy(); //Let the spawn point do any animations or whatever

	enemiesSpawned++;
	respawnTimer = respawnRate;
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
