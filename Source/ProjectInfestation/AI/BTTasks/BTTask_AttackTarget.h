// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_AttackTarget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTINFESTATION_API UBTTask_AttackTarget : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_AttackTarget();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory) override;
	
};
