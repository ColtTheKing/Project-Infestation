// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InfestationDelegates.generated.h"

// Simple Delegates 
DECLARE_DYNAMIC_DELEGATE(FSimpleDelegateSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSimpleMulticastDelegateSignature);

// AI Delegates
// Delegate type for when a actor's target perception changes.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTargetPerceptionUpdatedSignature, AActor*, originActor, AActor*, targetActor);

/**
 * A storage class that stores all the game's delegates. 
 * 
 * Only one instance should exist in the game and it should be in 
 * the InfestationGameState class.
 */
UCLASS()
class PROJECTINFESTATION_API UInfestationDelegates : public UObject
{
	GENERATED_BODY()

public:
	UInfestationDelegates() = default;

	// Called when an actor dies.
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
		FSimpleMulticastDelegateSignature onDeathDelegate;

	// Called when an actor finds it's target.
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
		FOnTargetPerceptionUpdatedSignature onTargetFoundDelegate;

	// Called when an actor loses it's target.
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
		FOnTargetPerceptionUpdatedSignature onTargetLostDelegate;
};
