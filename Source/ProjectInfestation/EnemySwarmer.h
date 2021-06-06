// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicEnemy.h"
#include "EnemySwarmer.generated.h"

/**
 *
 */
UCLASS()
class PROJECTINFESTATION_API AEnemySwarmer : public ABasicEnemy
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		int meleeDamage;

	// Default constructor
	AEnemySwarmer();

	// Called every frame
	void Tick(float DeltaTime) override;

protected:
	// Called on level load
	void BeginPlay() override;

};