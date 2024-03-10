// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_AttackTarget.h"

#include "EnemyAIController.h"

UBTTask_AttackTarget::UBTTask_AttackTarget()
{
	NodeName = TEXT("Attack Target");
}

EBTNodeResult::Type UBTTask_AttackTarget::ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory)
{
	TWeakObjectPtr<AEnemyAIController> enemyController = Cast<AEnemyAIController>(ownerComp.GetAIOwner());
	if (enemyController == nullptr)
		return EBTNodeResult::Failed;

	enemyController->MeleeAttack();
	FinishLatentTask(ownerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
