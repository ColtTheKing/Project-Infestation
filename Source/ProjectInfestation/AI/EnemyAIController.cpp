// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../EnemyCharacter.h"

AEnemyAIController::AEnemyAIController(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	blackboardComp = objectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComponent"));
	
	behaviorComp = objectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorTreeComponent"));
	BrainComponent = behaviorComp; // BrainComponent comes from the parent class.

	perceptionComp = objectInitializer.CreateDefaultSubobject<UAIPerceptionComponent>(this, TEXT("AIPerceptionComponent"));
}

void AEnemyAIController::MeleeAttack()
{
	// Should be overridden.
}

void AEnemyAIController::OnPossess(APawn* inPawn)
{
	Super::OnPossess(inPawn);

	// Set up blackboard and tree
	AEnemyCharacter* enemy = Cast<AEnemyCharacter>(inPawn);
	if (enemy && enemy->GetBehaviorTree())
	{
		if (enemy->GetBehaviorTree()->BlackboardAsset)
			blackboardComp->InitializeBlackboard(*enemy->GetBehaviorTree()->BlackboardAsset);

		behaviorComp->StartTree(*(enemy->GetBehaviorTree()));
	}
}

void AEnemyAIController::OnUnPossess()
{
	Super::OnUnPossess();

	behaviorComp->StopTree();
}
