// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AttackTargetInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAttackTargetInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface to be implemented by all attack targets.
 */
class PROJECTINFESTATION_API IAttackTargetInterface
{
	GENERATED_BODY()

public:

	/**
	 * Get the number of attackers that can attack the target at one time.
	 * 
	 * @return The number of attackers.
	 */
	virtual int GetMaxNumberOfAttackers() const = 0;
	
};
