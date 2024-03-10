// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_ContainsPatrolPath.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTINFESTATION_API UBTDecorator_ContainsPatrolPath : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_ContainsPatrolPath();
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory) const override;
};
