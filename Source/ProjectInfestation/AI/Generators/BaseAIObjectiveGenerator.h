// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagAssetInterface.h"

#include "../Objectives/AIObjective.h"

#include "BaseAIObjectiveGenerator.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class PROJECTINFESTATION_API UBaseAIObjectiveGenerator : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void OnUpdate();
	
	UFUNCTION(BlueprintCallable)
		UAIObjective* GetOrCreateObjective(TSubclassOf<UAIObjective> objectiveType);

	UFUNCTION(BlueprintCallable)
		TArray<UAIObjective*> GetExistingObjectives();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Objective Generator")
		FGameplayTag objectiveGeneratorType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Objective Generator")
		TArray<UAIObjective*> existingObjectives;
};
