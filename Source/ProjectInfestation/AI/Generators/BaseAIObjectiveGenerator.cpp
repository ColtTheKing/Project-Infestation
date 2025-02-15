// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAIObjectiveGenerator.h"

UAIObjective* UBaseAIObjectiveGenerator::GetOrCreateObjective(TSubclassOf<UAIObjective> objectiveType)
{
	return nullptr;
}

TArray<UAIObjective*> UBaseAIObjectiveGenerator::GetExistingObjectives()
{
	return existingObjectives;
}
