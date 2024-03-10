// Fill out your copyright notice in the Description page of Project Settings.

#include "BTDecorator_ContainsPatrolPath.h"

#include "../EnemyCharacter.h"
#include "EnemyAIController.h"

UBTDecorator_ContainsPatrolPath::UBTDecorator_ContainsPatrolPath()
{
	NodeName = TEXT("Actor Contains Patrol Path");
}

bool UBTDecorator_ContainsPatrolPath::CalculateRawConditionValue(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory) const
{
	AEnemyAIController* enemyController = Cast<AEnemyAIController>(ownerComp.GetAIOwner());
	if (enemyController == nullptr)
		return false;

	AEnemyCharacter* enemyPawn = Cast<AEnemyCharacter>(enemyController->GetPawn());
	if (enemyPawn == nullptr)
		return false;

	return enemyPawn->GetPatrolPath() != nullptr;
}