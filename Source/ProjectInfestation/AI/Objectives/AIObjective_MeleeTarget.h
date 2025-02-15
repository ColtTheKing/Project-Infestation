// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIObjective.h"
#include "AIObjective_MeleeTarget.generated.h"

USTRUCT(BlueprintType)
struct FUAIOpportunity_MeleeTarget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TWeakObjectPtr<AActor> targetActor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isTargetInSight = false;
};

/**
 * 
 */
UCLASS()
class PROJECTINFESTATION_API UAIObjective_MeleeTarget : public UAIObjective
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FUAIOpportunity_MeleeTarget> meleeTargetOpportunities = {};
};
