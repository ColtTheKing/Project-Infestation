// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "AIBehavior.h"
#include "Objectives/AIObjective.h"

#include "AIBehaviorGroup.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class PROJECTINFESTATION_API UAIBehaviorGroup : public UObject
{
	GENERATED_BODY()

public:
	UAIBehaviorGroup();

	// Are the conditions valid for this behavior group
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		bool AreStartingConditionsMet(AActor* aiActor, const TArray<UAIObjective*>& availableObjectives);

protected:
	// Name of the behavior group.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Behavior Group")
		FString behaviorName;

	// List of behaviors in group.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Behavior Group")
		TArray<TObjectPtr<UAIBehavior>> behaviors;

	// List of behavior groups in group.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Behavior Group")
		TArray<TObjectPtr<UAIBehaviorGroup>> behaviorGroups;

	// Cooldown time between when this behavior group can be selected again.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Behavior Group")
		double cooldownTime;
};
