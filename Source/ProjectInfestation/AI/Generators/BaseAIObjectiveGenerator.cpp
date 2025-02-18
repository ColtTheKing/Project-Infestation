// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAIObjectiveGenerator.h"

UBaseAIObjectiveGenerator::UBaseAIObjectiveGenerator()
{

}

UAIObjective* UBaseAIObjectiveGenerator::GetOrCreateObjective(TSubclassOf<UAIObjective> objectiveType)
{
	if (objectiveType == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s: ObjectiveType is invalid type."), *this->GetFName().ToString());
		return nullptr;
	}

	// Get existing
	for (auto& objective : existingObjectives)
	{
		if (objective->IsA(objectiveType))
			return objective;
	}
	
	// Create if it doesn't exist
	auto* newObjective = NewObject<UAIObjective>(this, objectiveType);
	existingObjectives.Add(newObjective);
	return newObjective;
}

TArray<UAIObjective*> UBaseAIObjectiveGenerator::GetExistingObjectives()
{
	return existingObjectives;
}

void UBaseAIObjectiveGenerator::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	TagContainer.AddTag(objectiveGeneratorType);
}
