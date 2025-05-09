// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBehaviour.h"

bool UAIBehaviour::IsValidSelectionOption() const
{
	return !IsCoolingDown() && AreStartingConditionsMet();
}

bool UAIBehaviour::IsCoolingDown() const
{
	return false;
}

bool UAIBehaviour::AreStartingConditionsMet() const
{
	return false;
}

float UAIBehaviour::GetSelectionScore() const
{
	return 0.0f;
}

void UAIBehaviour::StartBehaviour() const
{
}

void UAIBehaviour::StopBehaviour() const
{
}

void UAIBehaviour::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	TagContainer.AddTag(behaviourType);
}
