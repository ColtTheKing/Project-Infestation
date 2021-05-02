// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "EnemySwarmer.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTINFESTATION_API AEnemySwarmer : public AEnemyCharacter
{
	GENERATED_BODY()

public:
	// Default constructor
	AEnemySwarmer();

protected:
	// Called on level load
	void BeginPlay() override;

public:
	// Called every frame
	void Tick(float DeltaTime) override;

};
