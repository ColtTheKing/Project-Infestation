// Fill out your copyright notice in the Description page of Project Settings.

#include "AIObjectiveGenerationComponent.h"

#include "Perception/AIPerceptionComponent.h"

// Sets default values for this component's properties
UAIObjectiveGenerationComponent::UAIObjectiveGenerationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UAIObjectiveGenerationComponent::BeginPlay()
{
	Super::BeginPlay();

	// Set AIPerceptionComponent in generators
	UAIPerceptionComponent* perceptionComponent = GetOwner()->GetComponentByClass<UAIPerceptionComponent>();
	if (perceptionComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, 
			TEXT("%s: Perception component is null. Using a ObjectiveGenerationComponent requires the actor have a AIPerceptionComponent."), 
			*this->GetFName().ToString());
		return;
	}

	for (auto& generator : objectiveGenerators)
		generator->SetOwnerPerceptionComponent(perceptionComponent);
}


// Called every frame
void UAIObjectiveGenerationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAIObjectiveGenerationComponent::UpdateGenerators()
{
	if (objectiveGenerators.IsEmpty())
		UE_LOG(LogTemp, Warning, TEXT("%s: No generators added to call update on."), *this->GetFName().ToString());

	for (auto& generator : objectiveGenerators)
		generator->OnUpdate();
}

UBaseAIObjectiveGenerator* UAIObjectiveGenerationComponent::GetGenerator(TSubclassOf<UBaseAIObjectiveGenerator> objectiveGeneratorClass)
{
	if (objectiveGenerators.IsEmpty())
		UE_LOG(LogTemp, Warning, TEXT("%s: OpportunityGenerators array is empty."), *this->GetFName().ToString());

	for (auto& generator : objectiveGenerators)
	{
		if (generator->IsA(objectiveGeneratorClass))
			return generator;
	}
	return nullptr;
}
