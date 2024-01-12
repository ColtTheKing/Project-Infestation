// Fill out your copyright notice in the Description page of Project Settings.

#include "SwarmerAIController.h"

#include "../MyPlayerCharacter.h"

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

void ASwarmerAIController::HandleSightSense(AActor* actor, FAIStimulus const stimulus)
{
	// Only want to continue if the Actor sighted is the player.
	TWeakObjectPtr<AMyPlayerCharacter> player = Cast<AMyPlayerCharacter>(actor);
	if (player == nullptr)
		return;

	if (stimulus.WasSuccessfullySensed())
		// Player found.
		GetBlackboardComp()->SetValueAsObject("TargetActor", player.Get());
	else
		// Player lost.
		GetBlackboardComp()->SetValueAsObject("TargetActor", NULL);
}

void ASwarmerAIController::MeleeAttack()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Take Damage"));

	TWeakObjectPtr<AActor> actor = Cast<AActor>(GetBlackboardComp()->GetValueAsObject("TargetActor"));
	TWeakObjectPtr<AEnemyCharacter> enemy = Cast<AEnemyCharacter>(GetPawn());
	actor->TakeDamage(enemy->GetAttackDamage(), FDamageEvent(), this, enemy.Get());
}
