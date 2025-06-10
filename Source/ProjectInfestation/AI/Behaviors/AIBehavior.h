// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BehaviorTree/BehaviorTree.h"
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
		bool IsValidSelectionOption() const;

	// Is the Behavior currently cooling down?
	UFUNCTION(BlueprintCallable)
		bool IsCoolingDown() const;

	// Are the conditions valid for this Behavior to be started
	UFUNCTION(BlueprintCallable)
		virtual bool AreStartingConditionsMet() const;

	// Calculates a score used of Behavior selection when we have multiple options
	UFUNCTION(BlueprintCallable)
		virtual float GetSelectionScore() const;

	UFUNCTION(BlueprintCallable)
		void StartBehavior();

	UFUNCTION(BlueprintCallable)
		void StopBehavior();

	// From IGameplayTagAssetInterface
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Behavior")
		float maxCooldownTime;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Behavior")
		FString BehaviorName;

	// Behavior tree for Behavior
	UPROPERTY(EditAnywhere, Category = "AI Behavior")
		UBehaviorTree* behaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Behavior")
		FGameplayTag behaviorType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Behavior")
		TEnumAsByte<BehaviorState> executionState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Behavior")
		bool isInterruptible;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Behavior")
		float cooldownTimer;
};
