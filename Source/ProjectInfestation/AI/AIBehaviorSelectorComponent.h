// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Behaviors/AIBehavior.h"
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
	*/ 
	UFUNCTION(BlueprintCallable)
		FAIBehaviorOption SelectBehavior(const TArray<UAIObjective*>& availableObjectives);

	FORCEINLINE UAIBehavior* GetDefaultBehavior() { return defaultBehavior; }

private:
	// Helper functions for better readability in SelectBehavior function.
	bool GetValidBehaviorOptions(
		TArray<FAIBehaviorOption>& validBehaviorOptions, 
		const TArray<TObjectPtr<UAIBehavior>>& behaviors,
		const TArray<UAIObjective*>& availableObjectives);
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

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
		FAIBehaviorOption currentBehaviorOption;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced, meta = (AllowPrivateAccess = true))
		TArray<TObjectPtr<UAIBehavior>> highPriorityBehaviors;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced, meta=(AllowPrivateAccess=true))
		TArray<TObjectPtr<UAIBehavior>> behaviors;
};
