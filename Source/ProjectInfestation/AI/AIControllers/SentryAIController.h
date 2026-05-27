// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAIController.h"
#include "SentryAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTINFESTATION_API ASentryAIController : public AEnemyAIController
{
	GENERATED_BODY()

public:
	ASentryAIController(const FObjectInitializer& objectInitializer);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
