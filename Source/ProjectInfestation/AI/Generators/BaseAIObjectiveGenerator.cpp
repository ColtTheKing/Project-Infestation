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
	auto* objective = GetExistingObjective(objectiveType);
	if (objective != nullptr)
		return objective;
	
	// Create if it doesn't exist
	auto* newObjective = NewObject<UAIObjective>(this, objectiveType);
	existingObjectives.Add(newObjective);
	return newObjective;
}

UAIObjective* UBaseAIObjectiveGenerator::GetExistingObjective(TSubclassOf<UAIObjective> objectiveType)
{
	for (auto& objective : existingObjectives)
	{
		if (objective->IsA(objectiveType))
			return objective;
	}
	return nullptr;
}

TArray<UAIObjective*> UBaseAIObjectiveGenerator::GetExistingObjectives()
{
	return existingObjectives;
}

void UBaseAIObjectiveGenerator::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	TagContainer.AddTag(objectiveGeneratorType);
}
