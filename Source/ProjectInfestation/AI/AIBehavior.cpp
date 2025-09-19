// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBehavior.h"

UAIBehavior::UAIBehavior()
{
	executionMode = BehaviorExecutionMode::Looped;
	weight = 1;
}

void UAIBehavior::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	TagContainer.AddTag(behaviorType);
}

bool UAIBehavior::IsValidBlackboard(UBlackboardComponent* blackboardComp)
{
	return blackboardComp->GetBlackboardAsset() == GetBlackboardAsset();
}
