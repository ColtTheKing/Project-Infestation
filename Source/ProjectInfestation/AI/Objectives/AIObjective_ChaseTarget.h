// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIObjective.h"
#include "AIObjective_ChaseTarget.generated.h"

USTRUCT(BlueprintType)
struct FAIObjectiveOption_ChaseTarget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TWeakObjectPtr<AActor> targetActor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isTargetPlayer = false;

	// Distance before target is no longer considered. From chase search radius.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float maxTargetDistance = 0.0f;
};

/**
 * 
 */
UCLASS()
class PROJECTINFESTATION_API UAIObjective_ChaseTarget : public UAIObjective
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FAIObjectiveOption_ChaseTarget> chaseOptions = {};
};
