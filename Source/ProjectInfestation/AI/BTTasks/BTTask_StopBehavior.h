// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_StopBehavior.generated.h"

/**
 * Stop Behavior task node.
 * Stops the current behavior tree from running. Node required for behaviors that we want to be looped but also want to stop after meeting some conditions.
 */
UCLASS()
class PROJECTINFESTATION_API UBTTask_StopBehavior : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	explicit UBTTask_StopBehavior(FObjectInitializer const& objectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory) override;
	
};
