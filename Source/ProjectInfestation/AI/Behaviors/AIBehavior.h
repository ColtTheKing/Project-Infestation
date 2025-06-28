// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameplayTagAssetInterface.h"
#include "AIBehavior.generated.h"

UENUM(BlueprintType)
enum BehaviorState
{
	RUNNING		UMETA(DisplayName = "RUNNING"), 
	COMPLETED	UMETA(DisplayName = "COMPLETED"), 
	FAILED		UMETA(DisplayName = "FAILED")
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
	bool AreStartingConditionsMet();

	// Calculates a score used of Behavior selection when we have multiple options
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	int GetSelectionScore();

	// Function that takes a external blackboard component and sets variables in the blackboard asset
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateExternalBlackboard(UBlackboardComponent* blackboardComp);

	UFUNCTION(BlueprintCallable)
	void StartBehavior();

	UFUNCTION(BlueprintCallable)
	void StopBehavior();

	FORCEINLINE UBehaviorTree* GetBehaviorTree() const { return behaviorTree; }
	FORCEINLINE UBlackboardData* GetBlackboardAsset() const { return behaviorTree->GetBlackboardAsset(); }

	// From IGameplayTagAssetInterface
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior")
		float maxCooldownTime;

protected:
	UFUNCTION(BlueprintCallable)
		bool IsValidBlackboard(UBlackboardComponent* blackboardComp);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior")
		FString BehaviorName;

	// Behavior tree for Behavior
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Behavior")
		TObjectPtr<UBehaviorTree> behaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior")
		FGameplayTag behaviorType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior")
		TEnumAsByte<BehaviorState> executionState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior")
		bool isInterruptible;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior")
		float cooldownTimer;
};
