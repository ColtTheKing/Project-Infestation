// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AEnemyAIController::AEnemyAIController(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	blackboardComp = objectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));
	
	behaviorComp = objectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	BrainComponent = behaviorComp; // BrainComponent comes from the parent class.
}

void AEnemyAIController::OnPossess(APawn* inPawn)
{
	Super::OnPossess(inPawn);
}

void AEnemyAIController::OnUnPossess()
{
	Super::OnUnPossess();
}
