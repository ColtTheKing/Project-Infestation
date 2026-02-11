// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameplayTagAssetInterface.h"

#include "Objectives/AIObjective.h"

#include "AIBehavior.generated.h"

class UAIBehaviorGroup;

/*
	BTExecutionMode in BehaviorTreeTypes isn't a UENUM and thus can't be a UPROPERTY.
	This acts as a one-to-one representation of it that can be mapped to the original.
*/
UENUM() 
enum BehaviorExecutionMode
{
	SingleRun,
	Looped
};

/*
	The BehaviorOption struct groups a behavior with an objective/objective option together.
	This allows us to run behaviors with the information stored in objective options. Score is
	included for behavior selection and isn't necessary for behavior execution. 
*/
USTRUCT(BlueprintType)
struct FAIBehaviorOption
{
	GENERATED_BODY()

	FAIBehaviorOption() = default;

	FAIBehaviorOption(TObjectPtr<UAIBehavior> behavior) : behavior(behavior) { }
	
	FAIBehaviorOption(const FAIBehaviorOption& other) noexcept = default;
	
	FAIBehaviorOption(FAIBehaviorOption&& other) noexcept
	{
		behavior = other.behavior;
		associatedObjective = other.associatedObjective;
		associatedObjectiveOptionIndex = other.associatedObjectiveOptionIndex;
		score = other.score;

		other.behavior = nullptr;
		other.associatedObjective = nullptr;
		other.associatedObjectiveOptionIndex = -1;
		other.score = 0;
	}

	FAIBehaviorOption& operator=(const FAIBehaviorOption& other) = default;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TObjectPtr<UAIBehavior> behavior = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TObjectPtr<UAIObjective> associatedObjective = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int associatedObjectiveOptionIndex = -1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float score = 0;
};

UCLASS(BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class PROJECTINFESTATION_API UAIBehavior : public UObject, public IGameplayTagAssetInterface
{
	GENERATED_BODY()

public:
	UAIBehavior();

	// Are the conditions valid for this Behavior to be started
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	bool AreStartingConditionsMet(AActor* aiActor, const TArray<UAIObjective*>& availableObjectives);

	// Calculates a score used of Behavior selection when we have multiple options
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	FAIBehaviorOption GetBestBehaviorOption(AActor* aiActor, const TArray<UAIObjective*>& availableObjectives);

	// Function that takes a external blackboard component and sets variables in the blackboard asset
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateExternalBlackboard(UBlackboardComponent* blackboardComp, const FAIBehaviorOption& behaviorOption = FAIBehaviorOption());

	FORCEINLINE const UBehaviorTree* GetBehaviorTree() const { return behaviorTree; }

	FORCEINLINE const UBlackboardData* GetBlackboardAsset() const { return behaviorTree->GetBlackboardAsset(); }

	FORCEINLINE const FString GetBehaviorName() const { return behaviorName; }

	FORCEINLINE const bool IsInterruptible() const { return isInterruptible; }

	FORCEINLINE const double CooldownTime() const { return cooldownTime; }

	FORCEINLINE const UAIBehaviorGroup* GetParentGroup() const { return parentGroup; }

	FORCEINLINE EBTExecutionMode::Type GetExecutionMode() const
	{
		return (executionMode == BehaviorExecutionMode::SingleRun) ? EBTExecutionMode::SingleRun : EBTExecutionMode::Looped;
	}

	// Should only be called by the group the behavior is attached to.
	FORCEINLINE void SetParentGroup(TObjectPtr<UAIBehaviorGroup> behaviorGroup)
	{
		parentGroup = behaviorGroup;
	}

	// From IGameplayTagAssetInterface
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;

protected:
	// Helper function for determining if the blackboard component's blackboard asset 
	// is the same as this behavior's blackboard asset.
	UFUNCTION(BlueprintCallable)
		bool IsValidBlackboard(UBlackboardComponent* blackboardComp);

	// Name of the behavior
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior")
		FString behaviorName;

	// Type of behavior (e.g. Combat)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Behavior")
		FGameplayTag behaviorType;

	// Behavior tree for Behavior
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Behavior")
		TObjectPtr<UBehaviorTree> behaviorTree;

	// Execution mode of this behavior.
	UPROPERTY(EditDefaultsOnly, Category = "Behavior")
		TEnumAsByte<BehaviorExecutionMode> executionMode;

	// Can this behavior be interrupted while it is running.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior")
		bool isInterruptible;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior")
		float weight;

	// Cooldown time between when this behavior can be selected again.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Behavior")
		double cooldownTime;

	UPROPERTY(BlueprintReadOnly, Category="Behavior")
		TObjectPtr<UAIBehaviorGroup> parentGroup;
};
