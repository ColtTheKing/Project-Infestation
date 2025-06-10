// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBehavior.h"

UAIBehavior::UAIBehavior()
{
	cooldownTimer = 0;
}

void UAIBehavior::Tick(float DeltaTime)
{
	if(IsCoolingDown())
		cooldownTimer -= DeltaTime;
}

bool UAIBehavior::IsTickable() const
{
	return true;
}

bool UAIBehavior::IsTickableInEditor() const
{
	return false;
}

bool UAIBehavior::IsTickableWhenPaused() const
{
	return false;
}

TStatId UAIBehavior::GetStatId() const
{
	return TStatId();
}

bool UAIBehavior::IsValidSelectionOption() const
{
	return !IsCoolingDown() && AreStartingConditionsMet();
}

bool UAIBehavior::IsCoolingDown() const
{
	return cooldownTimer > 0;
}

bool UAIBehavior::AreStartingConditionsMet() const
{
	if (IsCoolingDown())
		return false;
	return true;
}

float UAIBehavior::GetSelectionScore() const
{
	return 0.0f;
}

void UAIBehavior::StartBehavior()
{
	executionState = BehaviorState::RUNNING;
}

void UAIBehavior::StopBehavior()
{
	executionState = BehaviorState::COMPLETED;
	cooldownTimer = maxCooldownTime;
}

void UAIBehavior::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	TagContainer.AddTag(behaviorType);
}
