// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBehaviorSelectorComponent.h"

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

	return FAIBehaviorOption();
}

