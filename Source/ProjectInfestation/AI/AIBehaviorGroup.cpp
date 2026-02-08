// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBehaviorGroup.h"

UAIBehaviorGroup::UAIBehaviorGroup()
{

}

bool UAIBehaviorGroup::GetValidBehaviorOptions(TArray<FAIBehaviorOption>& validBehaviorOptions, const TObjectPtr<AActor>& aiActor, const TArray<UAIObjective*>& availableObjectives) const
{
	return false;
}
