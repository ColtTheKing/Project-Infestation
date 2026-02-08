// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "AIBehavior.h"
#include "AIBehaviorGroup.h"
#include "Objectives/AIObjective.h"

#include "AIBehaviorSelectorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTINFESTATION_API UAIBehaviorSelectorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAIBehaviorSelectorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/* 
		Selects a new behavior option from a collection of available objectives usually provided by
		the objective generator component. If function fails to select a new behavior for any 
		reason, it will return a empty FAIBehaviorOption. Function will not work if called in
		BeginPlay (before OnPossess on the controller is called).

		Current behavior running is provided by the bahavior tree component on the AI controller.
	*/ 
	UFUNCTION(BlueprintCallable)
		FAIBehaviorOption SelectBehavior(const TArray<UAIObjective*>& availableObjectives, bool currentBehaviorRunning);
	
	/*
		Temp function for selecting behaviors with behavior groups. Will replace SelectBehavior once
		properly implemented and tested.
	*/
	UFUNCTION(BlueprintCallable)
		FAIBehaviorOption SelectBehavior_GroupVersion(const TArray<UAIObjective*>& availableObjectives, bool currentBehaviorRunning);

	/*
		Starts the inputted behavior's cooldown. 
		
		If the function fails, it will log the error and return without doing anything.
	*/
	UFUNCTION(BlueprintCallable)
		void StartBehaviorCooldown(const FAIBehaviorOption& behaviorOption);

	/*
		Checks the cooldown system to see if the inputted behavior is currently cooling down. 
	*/
	UFUNCTION(BlueprintCallable)
		bool IsBehaviorCoolingDown(UAIBehavior* behavior);

	FORCEINLINE UAIBehavior* GetDefaultBehavior() { return defaultBehavior; }

private:  
	/*
		Helper functions for better readability in SelectBehavior function. Checks which behaviors
		are valid and then stores the valid behaviors with their objectives (in behavior options) 
		in the inputted list.  
	*/
	bool GetValidBehaviorOptions(
		TArray<FAIBehaviorOption>& validBehaviorOptions, 
		const TArray<TObjectPtr<UAIBehavior>>& behaviors,
		const TArray<UAIObjective*>& availableObjectives);

	/*
		Helper functions for better readability in SelectBehavior function. Returns the index of 
		the behavior option with the highest score. If multiple have the highest score, the returned
		index will be random between the highest ones.
	*/
	size_t GetBestBehaviorOptionIndex(const TArray<FAIBehaviorOption>& validBehaviorOptions);

	/*
		Default behavior that will run:
		a. When the enemy spawns into the world.
	    b. When the behavior selector has no valid behavior options.

		Note that a default behavior will have no corresponding objective option. Objectives state
		what can be done in the world so no behaviors == no objectives generated. Default means
		no other behavior was valid.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced, meta=(AllowPrivateAccess=true))
		TObjectPtr<UAIBehavior> defaultBehavior;

	// Current Behavior Option that is running.
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
		FAIBehaviorOption currentBehaviorOption;

	// Behaviors of the AI that should always run when valid.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced, meta = (AllowPrivateAccess = true))
		TArray<TObjectPtr<UAIBehavior>> highPriorityBehaviors;

	// Behaviors of the AI.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced, meta=(AllowPrivateAccess=true))
		TArray<TObjectPtr<UAIBehavior>> behaviors;

	// ****** Behavior Groups (Temp) ******
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced, Category = "Behavior Groups (Temp)", meta = (AllowPrivateAccess = true))
		TObjectPtr<UAIBehaviorGroup> highPriorityBehaviorGroup;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced, Category = "Behavior Groups (Temp)", meta = (AllowPrivateAccess = true))
		TMap<FString, TObjectPtr<UAIBehaviorGroup>> behaviorGroups;

	// ************************************

	/*
		Collection of behaviors (names) and the last time (seconds) they're cooldown started. 
		Used for the behavior's cooldown system.
	*/
	TMap<FString, double> lastTimeBehaviorsCooldownStarted;
};
