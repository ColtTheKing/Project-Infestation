// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_IncrementPatrolPathIndex.h"

#include "../EnemyCharacter.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_IncrementPatrolPathIndex::UBTTask_IncrementPatrolPathIndex()
{
	NodeName = TEXT("Increment the Patrol Path Index");
}

EBTNodeResult::Type UBTTask_IncrementPatrolPathIndex::ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory)
{
	AEnemyAIController* enemyController = Cast<AEnemyAIController>(ownerComp.GetAIOwner());
	if (enemyController == nullptr)
		return EBTNodeResult::Failed;

	AEnemyCharacter* enemyPawn = Cast<AEnemyCharacter>(enemyController->GetPawn());
	if (enemyPawn == nullptr || enemyPawn->GetPatrolPath() == nullptr)
		return EBTNodeResult::Failed;

	UBlackboardComponent* enemyBlackboard = ownerComp.GetBlackboardComponent();
	if (enemyBlackboard == nullptr)
		return EBTNodeResult::Failed;

	int const numOfPoints = enemyPawn->GetPatrolPath()->Num();
	int const minIndex = 0;
	int const maxIndex = numOfPoints - 1;
	int32 index = enemyBlackboard->GetValueAsInt(GetSelectedBlackboardKey());

	if (biDirectional)
	{
		if (index >= maxIndex && direction == EDirectionType::Forward)
			direction = EDirectionType::Reverse;

		else if (index == minIndex && direction == EDirectionType::Reverse)
			direction = EDirectionType::Forward;

	}

	index = (direction == EDirectionType::Forward) ? index + 1 : index - 1;
	enemyBlackboard->SetValueAsInt(GetSelectedBlackboardKey(), index % numOfPoints);

	FinishLatentTask(ownerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
