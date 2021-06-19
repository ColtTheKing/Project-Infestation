// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/ActorComponent.h"

#include <queue>

#include "BasicEnemy.h"

#include "EnemySpawner.generated.h"

USTRUCT()
struct FEnemy
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere)
		TSubclassOf<AEnemyCharacter> enemyCharacterBP;

	UPROPERTY(EditAnywhere)
		float respawnChance;
};

UCLASS()
class PROJECTINFESTATION_API AEnemySpawner : public AActor
{
private:
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		TArray<struct FEnemy> enemies;

	UPROPERTY(EditAnywhere)
		unsigned int spawnLimit;

	UPROPERTY(EditAnywhere)
		float respawnRate;

	UFUNCTION()
		void SpawnEnemy();
	
	UBoxComponent* spawnArea;
	size_t enemiesSpawned;
	float respawnTimer;

	// Respawns enemy of specific tag
	FEnemy* GetRandomEnemy();

public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

	void HandleEnemyDespawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
