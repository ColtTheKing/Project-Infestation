// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAIObjectiveGenerator.h"
#include "CombatAIObjectiveGenerator.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTINFESTATION_API UCombatAIObjectiveGenerator : public UBaseAIObjectiveGenerator
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite)
		TArray<AActor*> chaseTargets;

	UPROPERTY(BlueprintReadWrite)
		TArray<AActor*> meleeTargets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat AI Objective Generator")
		float chaseSearchRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat AI Objective Generator")
		float meleeSearchRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat AI Objective Generator")
		TArray<TEnumAsByte<EObjectTypeQuery>> combatTargetTypes;
};
