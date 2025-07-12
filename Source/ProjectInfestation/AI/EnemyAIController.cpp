// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/CrowdFollowingComponent.h"

#include "../InfestationGameState.h"
#include "../EnemyCharacter.h"
#include "../CombatArea.h"

AEnemyAIController::AEnemyAIController(const FObjectInitializer& objectInitializer) 
	: Super(objectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
	blackboardComp = objectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComponent"));
	
	behaviorComp = objectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorTreeComponent"));
	BrainComponent = behaviorComp; // BrainComponent comes from the parent class.

	perceptionComp = objectInitializer.CreateDefaultSubobject<UAIPerceptionComponent>(this, TEXT("AIPerceptionComponent"));
	objectiveGenerationComp = objectInitializer.CreateDefaultSubobject<UAIObjectiveGenerationComponent>(this, TEXT("AIObjectiveGenerationComponent"));
	behaviorSelectorComp = objectInitializer.CreateDefaultSubobject<UAIBehaviorSelectorComponent>(this, TEXT("AIBehaviorSelectorComponent"));
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

void AEnemyAIController::RunBehavior(UAIBehavior* behavior)
{
	// If either is NULL then we don't want to continue.
	if (!behavior->GetBehaviorTree() || !behavior->GetBehaviorTree()->GetBlackboardAsset())
	{
		UE_LOG(LogTemp, Error, TEXT("%s: Behavior Tree of Behavior or BlackboardAsset of Behavior's Behavior Tree is NULL. Aborted function call."), *this->GetFName().ToString());
		return;
	}

	// Setup blackboard.
	blackboardComp->InitializeBlackboard(*behavior->GetBlackboardAsset());
	blackboardComp->SetValueAsObject("SelfActor", GetPawn());
	
	// Update Blackboard variables to the ones in the Behavior.
	behavior->UpdateExternalBlackboard(blackboardComp);

	// Run behavior.
	behaviorComp->StartTree(*behavior->GetBehaviorTree(), behavior->GetExecutionMode());
}

void AEnemyAIController::AlertLocalEnemies(AActor* attackTarget)
{
	// Get overlapping actors
	TSet<AActor*> overlappingActors;
	GetPawn()->GetOverlappingActors(overlappingActors);

	// Get CombatArea that the enemy is in
	TWeakObjectPtr<AActor> combatArea;
	for (AActor* actor : overlappingActors)
	{
		if (actor->IsA(ACombatArea::StaticClass()))
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

	// Only want to possess an enemy character for now
	AEnemyCharacter* enemy = Cast<AEnemyCharacter>(inPawn);
	if (enemy && behaviorSelectorComp->GetDefaultBehavior())
	{
		RunBehavior(behaviorSelectorComp->GetDefaultBehavior());
	}
}

void AEnemyAIController::OnUnPossess()
{
	Super::OnUnPossess();

	behaviorComp->StopTree();
}
