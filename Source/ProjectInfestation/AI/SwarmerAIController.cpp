// Fill out your copyright notice in the Description page of Project Settings.

#include "SwarmerAIController.h"
#include "GameplayTagAssetInterface.h"
#include "GameplayTagContainer.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

#include "../EnemyCharacter.h"

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

void ASwarmerAIController::MeleeAttack()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Take Damage"));

	TWeakObjectPtr<AActor> actor = Cast<AActor>(GetBlackboardComp()->GetValueAsObject("TargetActor"));
	TWeakObjectPtr<AEnemyCharacter> enemy = Cast<AEnemyCharacter>(GetPawn());
	actor->TakeDamage(enemy->GetAttackDamage(), FDamageEvent(), this, enemy.Get());
}
