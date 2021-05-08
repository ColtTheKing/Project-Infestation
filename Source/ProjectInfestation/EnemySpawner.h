// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "EnemyCharacter.h"
#include "Components/BoxComponent.h"

#include "EnemySpawner.generated.h"

UCLASS()
class PROJECTINFESTATION_API AEnemySpawner : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		TSubclassOf<AEnemyCharacter> enemyCharacterBP;

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
