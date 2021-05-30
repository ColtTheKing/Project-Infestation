// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "EnemyQueen.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTINFESTATION_API AEnemyQueen : public AEnemyCharacter
{
	GENERATED_BODY()
	
public:
	// Default constructor
	AEnemyQueen();

	// Called every frame
	void Tick(float DeltaTime) override;

protected:
	// Called on level load
	void BeginPlay() override;
};
