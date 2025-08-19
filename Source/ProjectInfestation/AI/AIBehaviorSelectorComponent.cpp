// Fill out your copyright notice in the Description page of Project Settings.

#include "AIBehaviorSelectorComponent.h"

#include "AIController.h"

// Sets default values for this component's properties
UAIBehaviorSelectorComponent::UAIBehaviorSelectorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UAIBehaviorSelectorComponent::BeginPlay()
{
	Super::BeginPlay();

	// Current behavior will start as the default behavior with no corresponding objective option.
	currentBehaviorOption = FAIBehaviorOption(defaultBehavior);
}


// Called every frame
void UAIBehaviorSelectorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FAIBehaviorOption UAIBehaviorSelectorComponent::SelectBehavior(const TArray<UAIObjective*>& availableObjectives)
{
	// TODO: Return to later when we know how to track the state of the behavior tree. 
	//       We only care if the behavior is interruptible if the behavior is still running.
	if (!currentBehaviorOption.behavior->IsInterruptible())
	{
		UE_LOG(LogTemp, Display, TEXT("%s: Current running behavior %s is unable to be interrupted."), *this->GetFName().ToString(), *currentBehaviorOption.behavior->GetBehaviorName());
		return FAIBehaviorOption();
	}

	// Find all valid high priority behavior options
	TArray<FAIBehaviorOption> validBehaviorOptions;
	if (!GetValidBehaviorOptions(validBehaviorOptions, highPriorityBehaviors, availableObjectives)) 
		return FAIBehaviorOption(); // Function failed, will already log issue.

	// If valid options exist return best one.
	if (validBehaviorOptions.Num() == 1)
	{
		return validBehaviorOptions[0];
	}
	else if (validBehaviorOptions.Num() > 1)
	{
		size_t bestBehaviorOptionIndex = GetBestBehaviorOptionIndex(validBehaviorOptions);
		return validBehaviorOptions[bestBehaviorOptionIndex];
	}

	// Find all valid normal priority behavior options.
	if (!GetValidBehaviorOptions(validBehaviorOptions, behaviors, availableObjectives))
		return FAIBehaviorOption();

	// If valid options exist return best one, otherwise return default.
	if (validBehaviorOptions.IsEmpty())
	{
		return FAIBehaviorOption(defaultBehavior);
	}
	else if (validBehaviorOptions.Num() == 1)
	{
		return validBehaviorOptions[0];
	}
	else if (validBehaviorOptions.Num() > 1)
	{
		size_t bestBehaviorOptionIndex = GetBestBehaviorOptionIndex(validBehaviorOptions);
		UE_LOG(LogTemp, Error, TEXT("%s: Current bestBehaviorOptionIndex is %d"), *this->GetFName().ToString(), bestBehaviorOptionIndex);
		return validBehaviorOptions[bestBehaviorOptionIndex];
	}

	// Invalid path (for compiler)
	return FAIBehaviorOption();
}

bool UAIBehaviorSelectorComponent::GetValidBehaviorOptions(
	TArray<FAIBehaviorOption>& validBehaviorOptions, 
	const TArray<TObjectPtr<UAIBehavior>>& behaviorList, 
	const TArray<UAIObjective*>& availableObjectives)
{
	// Error checking
	AAIController* ownerController = Cast<AAIController>(GetOwner());
	if (ownerController == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s: Owner actor is not a controller."), *this->GetFName().ToString());
		return false;
	}

	AActor* ownerActor = ownerController->GetPawn();
	if (ownerActor == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s: Function called in BeginPlay (before OnPossess call) or controller doesn't have controlled pawn."), *this->GetFName().ToString());
		return false;
	}

	// Get valid behaviors
	for (TObjectPtr<UAIBehavior> behavior : behaviorList)
	{
		if (behavior->AreStartingConditionsMet(ownerActor, availableObjectives))
		{
			auto bestBehaviorOption = behavior->GetBestBehaviorOption(ownerActor, availableObjectives);
			validBehaviorOptions.Add(bestBehaviorOption);
		}
	}
	return true;
}

size_t UAIBehaviorSelectorComponent::GetBestBehaviorOptionIndex(const TArray<FAIBehaviorOption>& validBehaviorOptions)
{
	size_t bestBehaviorOptionIndex = 0;
	for (int i = 1; i < validBehaviorOptions.Num(); ++i)
	{
		if (validBehaviorOptions[i].score > validBehaviorOptions[bestBehaviorOptionIndex].score)
			bestBehaviorOptionIndex = i;
	}
	return bestBehaviorOptionIndex;
}
