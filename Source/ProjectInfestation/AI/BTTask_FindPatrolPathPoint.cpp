// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPatrolPathPoint.h"

#include "../EnemyCharacter.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindPatrolPathPoint::UBTTask_FindPatrolPathPoint(FObjectInitializer const& objectInitializer)
{
	NodeName = TEXT("Find Next Point on Patrol Path");
}

EBTNodeResult::Type UBTTask_FindPatrolPathPoint::ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory)
{
	AEnemyAIController* enemyController = Cast<AEnemyAIController>(ownerComp.GetAIOwner());
	if (enemyController == nullptr)
		return EBTNodeResult::Failed;

	AEnemyCharacter* enemyPawn = Cast<AEnemyCharacter>(enemyController->GetPawn());
	if (enemyPawn == nullptr)
		return EBTNodeResult::Failed;

	UBlackboardComponent* enemyBlackboard = ownerComp.GetBlackboardComponent();
	if (enemyBlackboard == nullptr)
		return EBTNodeResult::Failed;

	int32 index = enemyBlackboard->GetValueAsInt(GetSelectedBlackboardKey());
	FVector point = enemyPawn->GetPatrolPath()->GetPatrolPoint(index);
	FVector globalPoint = enemyPawn->GetPatrolPath()->GetActorTransform().TransformPosition(point);

	enemyBlackboard->SetValueAsVector(patrolPathVectorKey.SelectedKeyName, globalPoint);
	FinishLatentTask(ownerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}