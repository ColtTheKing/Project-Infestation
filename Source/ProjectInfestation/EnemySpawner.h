// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/ActorComponent.h"
#include "Templates/SharedPointer.h"

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
	
	TWeakObjectPtr<UBoxComponent> spawnArea;
	size_t enemiesSpawned;
	float respawnTimer;

	TArray<struct FEnemy> enemies;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int spawnLimit;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float respawnRate;

	// Sets default values for this actor's properties
	AEnemySpawner();

	// Respawns enemy of specific tag
	UFUNCTION(BlueprintCallable)
		TSubclassOf<AEnemyCharacter> GetRandomEnemy();

	void SpawnEnemy();

	UFUNCTION(BlueprintImplementableEvent, Category = Spawn)
		void CreateEnemyActor(TSubclassOf<AEnemyCharacter> enemy, FVector location, FRotator rotation);

	UFUNCTION(BlueprintCallable)
		void HandleEnemyDespawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
