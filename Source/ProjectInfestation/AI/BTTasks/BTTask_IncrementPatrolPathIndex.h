// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_IncrementPatrolPathIndex.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTINFESTATION_API UBTTask_IncrementPatrolPathIndex : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	explicit UBTTask_IncrementPatrolPathIndex();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory) override;

private:
	enum class EDirectionType 
	{
		Forward, 
		Reverse
	};

	EDirectionType direction = EDirectionType::Forward;
};
