// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameplayTagAssetInterface.h"
#include "AIBehaviour.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTINFESTATION_API UAIBehaviour : public UObject, public IGameplayTagAssetInterface
{
	GENERATED_BODY()
	
public:

	// Can this behaviour be started i.e. is it valid option for selection?
	UFUNCTION(BlueprintCallable)
		bool IsValidSelectionOption() const;

	// Is the behaviour currently colling down?
	UFUNCTION(BlueprintCallable)
		bool IsCoolingDown() const;

	// Are the conditions valid for this behaviour to be started
	UFUNCTION(BlueprintCallable)
		virtual bool AreStartingConditionsMet() const;

	// Calculates a score used of behaviour selection when we have multiple options
	UFUNCTION(BlueprintCallable)
		virtual float GetSelectionScore() const;

	UFUNCTION(BlueprintCallable)
		void StartBehaviour() const;

	UFUNCTION(BlueprintCallable)
		void StopBehaviour() const;

	// From IGameplayTagAssetInterface
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Behaviour")
		FString behaviourName;

	// Behaviour tree for behaviour
	UPROPERTY(EditAnywhere, Category = "AI Behaviour")
		UBehaviorTree* behaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Behaviour")
		FGameplayTag behaviourType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Behaviour")
		bool isInterruptible;
};
