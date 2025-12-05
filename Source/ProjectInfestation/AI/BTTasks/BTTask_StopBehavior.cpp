// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_StopBehavior.h"

UBTTask_StopBehavior::UBTTask_StopBehavior(FObjectInitializer const& objectInitializer)
{
	NodeName = TEXT("Stop Behavior");
}

EBTNodeResult::Type UBTTask_StopBehavior::ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory)
{
	ownerComp.StopTree(EBTStopMode::Safe);
	return EBTNodeResult::Succeeded;
}
