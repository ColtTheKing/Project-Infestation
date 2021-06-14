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
		unsigned int spawnLimit;
	
	UPROPERTY(EditAnywhere)
		float respawnTimer;
};

UCLASS()
class PROJECTINFESTATION_API AEnemySpawner : public AActor
{
private:
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		TArray<struct FEnemy> enemies;

	UFUNCTION()
		void SpawnEnemy(TSubclassOf<AEnemyCharacter> enemyBP);
	
	UBoxComponent* spawnArea;
	std::queue<FName> respawnQueue;
	bool enemyRespawning;

	// Respawns enemy of specific tag
	void RespawnEnemy(FName enemyTag);

public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

	void AddEnemyToRespawnQueue(FName enemyTag);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
