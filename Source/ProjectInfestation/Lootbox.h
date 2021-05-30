// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableActor.h"
#include "Components/BoxComponent.h"

#include "Lootbox.generated.h"

USTRUCT()
struct FLoot
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> lootBP;

	UPROPERTY(EditAnywhere, Category = "Loot", meta = (ClampMin = "0.0", ClampMax = "1.0"))
		float spawnChance;

	UPROPERTY(EditAnywhere)
		unsigned int spawnLimit;
};

/**
 * 
 */
UCLASS()
class PROJECTINFESTATION_API ALootbox : public AInteractableActor
{
	GENERATED_BODY()

	UBoxComponent* spawnArea;

	bool opened;

public:
	// Default constuctor
	ALootbox();

	UPROPERTY(EditAnywhere)
		TArray<struct FLoot> loots;

	UFUNCTION(BlueprintCallable)
		void SpawnLoot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
