// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "EnemyCharacter.h"
#include "Components/BoxComponent.h"

#include "EnemySpawner.generated.h"

USTRUCT()
struct FEnemy
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere)
		TSubclassOf<AEnemyCharacter> enemyCharacterBP;
	
	UPROPERTY(EditAnywhere)
		int spawn_limit;
	
	UPROPERTY(EditAnywhere)
		float respawn_timer;
};

UCLASS()
class PROJECTINFESTATION_API AEnemySpawner : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		TArray<struct FEnemy> enemies;

	UBoxComponent* spawnArea;
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
