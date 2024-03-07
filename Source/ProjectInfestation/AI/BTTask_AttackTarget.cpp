// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_AttackTarget.h"

#include "EnemyAIController.h"

UBTTask_AttackTarget::UBTTask_AttackTarget()
{
	NodeName = "Attack Target";
}

EBTNodeResult::Type UBTTask_AttackTarget::ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory)
{
	AEnemyAIController* enemyController = Cast<AEnemyAIController>(ownerComp.GetAIOwner());
	if (enemyController == NULL)
		return EBTNodeResult::Failed;

	enemyController->MeleeAttack();
	FinishLatentTask(ownerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
