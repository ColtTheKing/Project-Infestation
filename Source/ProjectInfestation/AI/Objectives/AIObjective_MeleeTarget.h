// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIObjective.h"
#include "AIObjective_MeleeTarget.generated.h"

USTRUCT(BlueprintType)
struct FAIObjectiveOption_MeleeTarget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TWeakObjectPtr<AActor> targetActor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isTargetPlayer = false;

	// How far the attack can reach. From melee search radius.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float maxMeleeRange = 0.0f;
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
		TArray<FAIObjectiveOption_MeleeTarget> meleeOptions = {};
};
