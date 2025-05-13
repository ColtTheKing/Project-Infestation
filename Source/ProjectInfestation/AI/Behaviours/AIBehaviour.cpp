// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBehaviour.h"

UAIBehaviour::UAIBehaviour()
{
	cooldownTimer = 0;
}

void UAIBehaviour::Tick(float DeltaTime)
{
	if(IsCoolingDown())
		cooldownTimer -= DeltaTime;
}

bool UAIBehaviour::IsTickable() const
{
	return true;
}

bool UAIBehaviour::IsTickableInEditor() const
{
	return false;
}

bool UAIBehaviour::IsTickableWhenPaused() const
{
	return false;
}

TStatId UAIBehaviour::GetStatId() const
{
	return TStatId();
}

bool UAIBehaviour::IsValidSelectionOption() const
{
	return !IsCoolingDown() && AreStartingConditionsMet();
}

bool UAIBehaviour::IsCoolingDown() const
{
	return cooldownTimer > 0;
}

bool UAIBehaviour::AreStartingConditionsMet() const
{
	if (IsCoolingDown())
		return false;
	return true;
}

float UAIBehaviour::GetSelectionScore() const
{
	return 0.0f;
}

void UAIBehaviour::StartBehaviour()
{
	executionState = BehaviourState::RUNNING;
}

void UAIBehaviour::StopBehaviour()
{
	executionState = BehaviourState::COMPLETED;
	cooldownTimer = maxCooldownTime;
}

void UAIBehaviour::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	TagContainer.AddTag(behaviourType);
}
