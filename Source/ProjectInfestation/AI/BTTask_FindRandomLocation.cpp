// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_FindRandomLocation.h"

#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyAIController.h"

UBTTask_FindRandomLocation::UBTTask_FindRandomLocation()
{
	NodeName = "Find Random Location in NavMesh";
}

EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory)
{
	AEnemyAIController* enemyController = Cast<AEnemyAIController>(ownerComp.GetAIOwner());
	if (enemyController == NULL)
		return EBTNodeResult::Failed;

	APawn* enemyPawn = enemyController->GetPawn();
	if (enemyPawn != NULL)
	{
		FVector origin = enemyPawn->GetActorLocation();
		
		UNavigationSystemV1* navSystem = UNavigationSystemV1::GetCurrent(GetWorld());
		if (navSystem != NULL)
		{
			FNavLocation loc;
			if (navSystem->GetRandomPointInNavigableRadius(origin, searchRadius, loc))
			{
				ownerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), loc.Location);
			}

			FinishLatentTask(ownerComp, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
