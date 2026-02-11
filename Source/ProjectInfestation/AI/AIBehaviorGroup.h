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

	void PostInitProperties();

	// Are the conditions valid for this behavior group
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		bool AreStartingConditionsMet(AActor* aiActor, const TArray<UAIObjective*>& availableObjectives);

	FORCEINLINE const FString GetGroupName() const { return groupName; }
	FORCEINLINE const TMap<FString, TObjectPtr<UAIBehavior>>& GetBehaviors() const { return behaviors; }
	FORCEINLINE const TMap<FString, TObjectPtr<UAIBehaviorGroup>>& GetSubGroups() const { return subGroups; }

protected:
	// Name of the behavior group.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Behavior Group")
		FString groupName;

	// List of behaviors in group.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced, Category="Behavior Group")
		TMap<FString, TObjectPtr<UAIBehavior>> behaviors;

	// List of behavior groups in group.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced, Category="Behavior Group")
		TMap<FString, TObjectPtr<UAIBehaviorGroup>> subGroups;

	// Cooldown time between when this behavior group can be selected again.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Behavior Group")
		double cooldownTime;
};
