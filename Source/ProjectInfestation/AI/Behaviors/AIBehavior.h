// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameplayTagAssetInterface.h"

#include "../Objectives/AIObjective.h"

#include "AIBehavior.generated.h"

// BTExecutionMode in BehaviorTreeTypes isn't a UENUM and thus can't be a UPROPERTY.
// This acts as a one-to-one representation of it that can be mapped to the original.
UENUM() 
enum BehaviorExecutionMode
{
	SingleRun,
	Looped
};

UENUM(BlueprintType)
enum BehaviorState
{
	RUNNING		UMETA(DisplayName = "RUNNING"), 
	COMPLETED	UMETA(DisplayName = "COMPLETED"), 
	FAILED		UMETA(DisplayName = "FAILED")
};

USTRUCT(BlueprintType)
struct FAIBehaviorOption
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TWeakObjectPtr<UAIBehavior> behavior = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TWeakObjectPtr<UAIObjective> associatedObjective = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int associatedObjectiveOptionIndex = -1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float score = 0;
};

UCLASS(BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class PROJECTINFESTATION_API UAIBehavior : public UObject, public IGameplayTagAssetInterface, public FTickableGameObject
{
	GENERATED_BODY()

public:
	UAIBehavior();

	void Tick(float DeltaTime) override;
	bool IsTickable() const override;
	bool IsTickableInEditor() const override;
	bool IsTickableWhenPaused() const override;
	TStatId GetStatId() const override;

	// Can this Behavior be started i.e. is it valid option for selection?
	UFUNCTION(BlueprintCallable)
	bool IsValidSelectionOption();

	// Is the Behavior currently cooling down?
	UFUNCTION(BlueprintCallable)
	bool IsCoolingDown() const;

	// Are the conditions valid for this Behavior to be started
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	bool AreStartingConditionsMet(AActor* aiActor, const TArray<UAIObjective*>& availableObjectives);

	// Calculates a score used of Behavior selection when we have multiple options
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	FAIBehaviorOption GetBestBehaviorOption(AActor* aiActor, const TArray<UAIObjective*>& availableObjectives);

	// Function that takes a external blackboard component and sets variables in the blackboard asset
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateExternalBlackboard(UBlackboardComponent* blackboardComp, const FAIBehaviorOption& behaviorOption);

	UFUNCTION(BlueprintCallable)
	void StartBehavior();

	UFUNCTION(BlueprintCallable)
	void StopBehavior();

	FORCEINLINE UBehaviorTree* GetBehaviorTree() const { return behaviorTree; }
	FORCEINLINE UBlackboardData* GetBlackboardAsset() const { return behaviorTree->GetBlackboardAsset(); }
	
	FORCEINLINE EBTExecutionMode::Type GetExecutionMode() const
	{
		return (executionMode == BehaviorExecutionMode::SingleRun) ? EBTExecutionMode::SingleRun : EBTExecutionMode::Looped;
	}

	// From IGameplayTagAssetInterface
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior")
		float maxCooldownTime;

protected:
	UFUNCTION(BlueprintCallable)
		bool IsValidBlackboard(UBlackboardComponent* blackboardComp);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior")
		FString BehaviorName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Behavior")
		FGameplayTag behaviorType;

	// Behavior tree for Behavior
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Behavior")
		TObjectPtr<UBehaviorTree> behaviorTree;

	UPROPERTY(EditDefaultsOnly, Category = "Behavior")
		TEnumAsByte<BehaviorExecutionMode> executionMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior")
		TEnumAsByte<BehaviorState> executionState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior")
		bool isInterruptible;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior")
		float cooldownTimer;
};
