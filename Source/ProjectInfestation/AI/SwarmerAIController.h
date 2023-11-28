// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAIController.h"
#include "SwarmerAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTINFESTATION_API ASwarmerAIController : public AEnemyAIController
{
	GENERATED_BODY()

public:
	
	ASwarmerAIController(const FObjectInitializer& objectInitializer);

};
