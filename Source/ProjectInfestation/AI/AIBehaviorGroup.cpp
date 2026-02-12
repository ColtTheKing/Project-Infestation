// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBehaviorGroup.h"

UAIBehaviorGroup::UAIBehaviorGroup()
{

}

void UAIBehaviorGroup::PostInitProperties()
{
	Super::PostInitProperties();

	// Set parent group in child behavior
	for (const auto& [behaviorKey, behavior] : behaviors)
	{
		if (behavior != nullptr)
		{
			behavior->SetParentGroup(this);
		}
	}

	// Set parent group in sub groups
	for (const auto& [subGroupKey, subGroup] : subGroups)
	{
		if (subGroup != nullptr)
		{
			subGroup->SetParentGroup(this);
		}
	}
}
