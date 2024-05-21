// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_FindRandomLocation.h"

#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyAIController.h"

UBTTask_FindRandomLocation::UBTTask_FindRandomLocation()
{
	NodeName = TEXT("Find Random Location in NavMesh");
}

EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory)
{
	TWeakObjectPtr<AEnemyAIController> enemyController = Cast<AEnemyAIController>(ownerComp.GetAIOwner());
	if (enemyController == nullptr)
		return EBTNodeResult::Failed;

	TWeakObjectPtr<APawn> enemyPawn = enemyController->GetPawn();
	if (enemyPawn != nullptr)
	{
		FVector origin = enemyPawn->GetActorLocation();
		
		TWeakObjectPtr<UNavigationSystemV1> navSystem = UNavigationSystemV1::GetCurrent(GetWorld());
		if (navSystem != nullptr)
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
