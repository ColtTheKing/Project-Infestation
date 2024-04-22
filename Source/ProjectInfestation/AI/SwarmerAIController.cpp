// Fill out your copyright notice in the Description page of Project Settings.

#include "SwarmerAIController.h"

#include "../MyPlayerCharacter.h"

#include "GameplayTagAssetInterface.h"
#include "GameplayTagContainer.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

ASwarmerAIController::ASwarmerAIController(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	/*if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("TEST"));*/
}

void ASwarmerAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TWeakObjectPtr<AActor> actor = Cast<AActor>(GetBlackboardComp()->GetValueAsObject("TargetActor"));
	if (actor != nullptr)
	{
		TWeakObjectPtr<AEnemyCharacter> enemy = Cast<AEnemyCharacter>(GetPawn());
		float distance = enemy->GetDistanceTo(actor.Get());
		GetBlackboardComp()->SetValueAsBool("TargetInRange", distance <= enemy->GetAttackRadius());
	}
}

void ASwarmerAIController::UpdateAttackTarget(AActor* actor, FAIStimulus const stimulus)
{
	// Check if the actor sensed implements gameplay tags
	IGameplayTagAssetInterface* taggedActor = Cast<IGameplayTagAssetInterface>(actor);
	if (taggedActor == nullptr)
		return;

	// Check if the actor sensed has any tags matching an attack target
	TWeakObjectPtr<AEnemyCharacter> enemy = Cast<AEnemyCharacter>(GetPawn());
	if (!taggedActor->HasAnyMatchingGameplayTags(enemy->GetAttackTargets()))
		return;
	
	if (stimulus.WasSuccessfullySensed())
	{
		// Target found.
		GetBlackboardComp()->SetValueAsObject("TargetActor", actor);
	}
	else
	{
		// Target lost.
		GetBlackboardComp()->SetValueAsObject("TargetActor", NULL);
	}
}

void ASwarmerAIController::MeleeAttack()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Take Damage"));

	TWeakObjectPtr<AActor> actor = Cast<AActor>(GetBlackboardComp()->GetValueAsObject("TargetActor"));
	TWeakObjectPtr<AEnemyCharacter> enemy = Cast<AEnemyCharacter>(GetPawn());
	actor->TakeDamage(enemy->GetAttackDamage(), FDamageEvent(), this, enemy.Get());
}
