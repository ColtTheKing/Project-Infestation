// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_AttackTarget.h"

UBTTask_AttackTarget::UBTTask_AttackTarget()
{
	NodeName = "Attack Target";
}

EBTNodeResult::Type UBTTask_AttackTarget::ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory)
{
	return EBTNodeResult::Failed;
}
