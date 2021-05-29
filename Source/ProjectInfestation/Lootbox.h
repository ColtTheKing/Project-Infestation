// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableActor.h"
#include "Components/BoxComponent.h"

#include "Lootbox.generated.h"

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
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Loot", meta = (ClampMin = "0.0", ClampMax = "1.0"))
		float healthSpawnChance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Loot", meta = (ClampMin = "0.0", ClampMax = "1.0"))
		float ammoSpawnChance;

	UPROPERTY(EditAnywhere, Category = "Loot")
		TSubclassOf<AActor> healthBP;

	UFUNCTION(BlueprintCallable)
		void SpawnLoot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
