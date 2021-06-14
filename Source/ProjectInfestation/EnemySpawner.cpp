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
	enemyRespawning = false;

	// Spawn enemies
	for (auto& enemy : enemies)
	{
		unsigned int i = 0;
		while (i < enemy.spawnLimit)
		{
			SpawnEnemy(enemy.enemyCharacterBP);
			i++;
		}
	}

	// Respawn test
	// FName enemyToRespawnTag = FName(TEXT("Swarmer"));
	// RespawnEnemy(enemyToRespawnTag);
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!respawnQueue.empty() && !enemyRespawning) 
	{
		enemyRespawning = true;
		FName enemyToRespawnTag = respawnQueue.front();
		respawnQueue.pop();
		RespawnEnemy(enemyToRespawnTag);
	}
}

void AEnemySpawner::SpawnEnemy(TSubclassOf<AEnemyCharacter> enemyBP)
{
	// Enemy is no longer queued to respawn
	enemyRespawning = false;
	
	if (!enemyBP)
		return;

	// Calculate bounding box
	FTransform localToWorld = FTransform(GetActorLocation());
	FBox boundingBox = FBox::BuildAABB(localToWorld.GetLocation(), spawnArea->GetScaledBoxExtent());

	// TODO: Possible performance issue as if there is too many enemies it might turn into a infinite loop
	// Loop until found place to spawn
	while (true)
	{
		// Calculate random location in bounding box
		FVector randomLocation;
		randomLocation = boundingBox.Min;
		randomLocation.X += FGenericPlatformMath::FRand() * (boundingBox.Max.X - boundingBox.Min.X);
		randomLocation.Y += FGenericPlatformMath::FRand() * (boundingBox.Max.Y - boundingBox.Min.Y);
		randomLocation.Z += FGenericPlatformMath::FRand() * (boundingBox.Max.Z - boundingBox.Min.Z);

		// Spawn a enemy
		FRotator spawnRotation = FRotator(0.0f, 0.0f, 0.0f);
		ABasicEnemy* spawnedEnemy = Cast<ABasicEnemy>(GetWorld()->SpawnActor(enemyBP, &randomLocation, &spawnRotation));

		if (IsValid(spawnedEnemy))
		{
			spawnedEnemy->SetEnemySpawner(this);
			break;
		}
	}
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
		enemyRespawning = false;
		return;
	}
	
	FTimerDelegate TimerDel;
	FTimerHandle TimerHandle;

	TimerDel.BindUFunction(this, FName("SpawnEnemy"), enemyToSpawn.enemyCharacterBP);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, enemyToSpawn.respawnTimer, false);
}

void AEnemySpawner::AddEnemyToRespawnQueue(FName enemyTag)
{
	UE_LOG(LogTemp, Warning, TEXT("Enemy added to respawn queue"));
	respawnQueue.push(enemyTag);
}
