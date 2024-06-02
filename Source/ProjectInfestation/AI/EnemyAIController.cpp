// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "../InfestationGameState.h"
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

bool AEnemyAIController::ValidAttackTarget(AActor* actor)
{
	// Check if the actor sensed implements gameplay tags
	IGameplayTagAssetInterface* taggedActor = Cast<IGameplayTagAssetInterface>(actor);
	if (taggedActor == nullptr)
		return false;

	// Check if the actor sensed has any tags matching an attack target
	AEnemyCharacter* enemy = Cast<AEnemyCharacter>(GetPawn());
	if (!taggedActor->HasAnyMatchingGameplayTags(enemy->GetAttackTargets()))
		return false;

	// If passed all conditions
	return true;
}

void AEnemyAIController::SetAttackTarget(AActor* attackTarget)
{
	targetActor = attackTarget;
	blackboardComp->SetValueAsObject("TargetActor", attackTarget);
}

bool AEnemyAIController::WasSuccussfullySensed(FAIStimulus const stimulus)
{
	return stimulus.WasSuccessfullySensed();
}

void AEnemyAIController::AlertLocalEnemies(AActor* attackTarget)
{
	// Get overlapping actors
	TSet<AActor*> overlappingActors;
	GetPawn()->GetOverlappingActors(overlappingActors);

	// Get CombatArea that the enemy is in
	// TODO: Replace hardcoded check for CombatArea
	TWeakObjectPtr<AActor> combatArea;
	for (AActor* actor : overlappingActors)
	{
		if (actor->GetName().Contains("CombatArea"))
		{
			combatArea = actor;
			break;
		}
	}

	// If doesn't exist, return
	if (!combatArea.IsValid())
		return;

	// Alert the local enemies
	// TODO: Move this code to a separate CombatArea class in the form of a function.
	//       This makes the implementation cleaner. However, currently there isn't 
	//       any benefit to doing this.
	combatArea->GetOverlappingActors(overlappingActors);
	for (AActor* actor : overlappingActors)
	{
		// Don't want to alert this enemy actor
		if (actor == GetPawn())
			continue;

		TWeakObjectPtr<AEnemyCharacter> enemy = Cast<AEnemyCharacter>(actor);
		if (enemy != nullptr)
		{
			// Set attack target
			TWeakObjectPtr<AEnemyAIController> enemyController = Cast<AEnemyAIController>(enemy->GetController());
			enemyController->SetAttackTarget(attackTarget);

			// Broadcast to combat manager
			AInfestationGameState* state = Cast<AInfestationGameState>(GetWorld()->GetGameState());
			state->GetDelegates()->onTargetFoundDelegate.Broadcast(actor, attackTarget);
		}
	}
}

void AEnemyAIController::OnPossess(APawn* inPawn)
{
	Super::OnPossess(inPawn);

	// Set up blackboard and tree
	AEnemyCharacter* enemy = Cast<AEnemyCharacter>(inPawn);
	if (enemy && enemy->GetBehaviorTree())
	{
		if (enemy->GetBehaviorTree()->BlackboardAsset)
		{
			blackboardComp->InitializeBlackboard(*enemy->GetBehaviorTree()->BlackboardAsset);
			blackboardComp->SetValueAsObject("SelfActor", enemy);
		}

		behaviorComp->StartTree(*(enemy->GetBehaviorTree()));
	}
}

void AEnemyAIController::OnUnPossess()
{
	Super::OnUnPossess();

	behaviorComp->StopTree();
}
