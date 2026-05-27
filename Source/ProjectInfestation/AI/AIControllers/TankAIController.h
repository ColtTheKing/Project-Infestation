// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTINFESTATION_API ATankAIController : public AEnemyAIController
{
	GENERATED_BODY()

public:
	ATankAIController(const FObjectInitializer& objectInitializer);

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
