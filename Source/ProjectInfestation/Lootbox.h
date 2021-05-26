// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableActor.h"
#include "Lootbox.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTINFESTATION_API ALootbox : public AInteractableActor
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, Category = "Loot", meta = (ClampMin = "0.0", ClampMax = "1.0"))
		float healthSpawnChance;

	UPROPERTY(EditAnywhere, Category = "Loot", meta = (ClampMin = "0.0", ClampMax = "1.0"))
		float ammoSpawnChance;
	
	ALootbox();

};
