// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "EnemyCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/ActorComponent.h"

#include <string>

#include "EnemySpawner.generated.h"

USTRUCT()
struct FEnemy
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere)
		TSubclassOf<AEnemyCharacter> enemyCharacterBP;
	
	UPROPERTY(EditAnywhere)
		int spawnLimit;
	
	UPROPERTY(EditAnywhere)
		float respawnTimer;
};

UCLASS()
class PROJECTINFESTATION_API AEnemySpawner : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		TArray<struct FEnemy> enemies;

	UFUNCTION()
		void SpawnEnemy(TSubclassOf<AEnemyCharacter> enemyBP);

	UBoxComponent* spawnArea;
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

	// Respawns enemy of specific tag
	void RespawnEnemy(FName enemyTag);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
