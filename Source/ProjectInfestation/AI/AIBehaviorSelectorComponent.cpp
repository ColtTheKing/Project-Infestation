// Fill out your copyright notice in the Description page of Project Settings.

#include "AIBehaviorSelectorComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "AIController.h"
#include "../InfestationLogging.h"

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

FAIBehaviorOption UAIBehaviorSelectorComponent::SelectBehavior(const TArray<UAIObjective*>& availableObjectives, bool currentBehaviorRunning)
{
	if (currentBehaviorRunning && !currentBehaviorOption.behavior->IsInterruptible())
	{
		UE_LOG(LogInfestationAISystem, Display, TEXT("%s: Current running behavior %s is unable to be interrupted."), *this->GetFName().ToString(), *currentBehaviorOption.behavior->GetBehaviorName());
		return FAIBehaviorOption();
	}

	// Find all valid high priority behavior options and return best one.
	TArray<FAIBehaviorOption> validBehaviorOptions;
	if (!GetValidBehaviorOptions(validBehaviorOptions, highPriorityBehaviors, availableObjectives)) 
		return FAIBehaviorOption(); // Function failed, will already log issue.

	if (validBehaviorOptions.Num() == 1)
	{
		return validBehaviorOptions[0];
	}
	else if (validBehaviorOptions.Num() > 1)
	{
		size_t bestBehaviorOptionIndex = GetBestBehaviorOptionIndex(validBehaviorOptions);
		if (bestBehaviorOptionIndex < 0) return FAIBehaviorOption(); // Function failed, will already log issue.
		return validBehaviorOptions[bestBehaviorOptionIndex];
	}

	// Find all valid normal priority behavior options and return best one.
	if (!GetValidBehaviorOptions(validBehaviorOptions, behaviors, availableObjectives))
		return FAIBehaviorOption();

	if (validBehaviorOptions.IsEmpty())
	{
		return FAIBehaviorOption(defaultBehavior);
	}
	else if (validBehaviorOptions.Num() == 1)
	{
		return validBehaviorOptions[0];
	}
	else // validBehaviorOptions.Num() > 1
	{
		size_t bestBehaviorOptionIndex = GetBestBehaviorOptionIndex(validBehaviorOptions);
		if (bestBehaviorOptionIndex < 0) return FAIBehaviorOption();
		return validBehaviorOptions[bestBehaviorOptionIndex];
	}
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
		UE_LOG(LogInfestationAISystem, Error, TEXT("%s: Owner actor is not a controller."), *this->GetFName().ToString());
		return false;
	}

	AActor* ownerActor = ownerController->GetPawn();
	if (ownerActor == nullptr)
	{
		UE_LOG(LogInfestationAISystem, Error, TEXT("%s: Function called in BeginPlay (before OnPossess call) or controller doesn't have controlled pawn."), *this->GetFName().ToString());
		return false;
	}

	// Get valid behaviors
	for (TObjectPtr<UAIBehavior> behavior : behaviorList)
	{
		if (behavior != nullptr && 
			behavior->AreStartingConditionsMet(ownerActor, availableObjectives))
		{
			auto bestBehaviorOption = behavior->GetBestBehaviorOption(ownerActor, availableObjectives);
			validBehaviorOptions.Add(bestBehaviorOption);
		}
	}
	return true;
}

size_t UAIBehaviorSelectorComponent::GetBestBehaviorOptionIndex(const TArray<FAIBehaviorOption>& validBehaviorOptions)
{
	TArray<size_t> bestBehaviorOptionIndices({ 0 });
	for (int i = 1; i < validBehaviorOptions.Num(); ++i)
	{
		size_t bestBehaviorOptionIndex = bestBehaviorOptionIndices[0];
		if (validBehaviorOptions[i].score > validBehaviorOptions[bestBehaviorOptionIndex].score)
		{
			bestBehaviorOptionIndices.Empty(1);
			bestBehaviorOptionIndices.Add(i);
		}
		else if (validBehaviorOptions[i].score == validBehaviorOptions[bestBehaviorOptionIndex].score)
		{
			bestBehaviorOptionIndices.Add(i);
		}
	}

	if (bestBehaviorOptionIndices.Num() == 0)
	{
		UE_LOG(LogInfestationAISystem, Error, TEXT("%s: no best behavior option found, this is a bug."), *this->GetFName().ToString());
		return -1;
	}

	if (bestBehaviorOptionIndices.Num() == 1)
		return bestBehaviorOptionIndices[0];

	int32 index = UKismetMathLibrary::RandomInteger(bestBehaviorOptionIndices.Num());
	return bestBehaviorOptionIndices[index];
}

