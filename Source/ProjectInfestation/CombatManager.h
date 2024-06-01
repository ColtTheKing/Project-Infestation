// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "InfestationGameState.h"
#include "EnemyCharacter.h"
#include "AI/EnemyAIController.h"
#include "CombatManager.generated.h"

USTRUCT()
struct FAttackTarget
{
	GENERATED_USTRUCT_BODY()

	FAttackTarget() = default;

	FAttackTarget(uint32 targetActorID) : targetActorID(targetActorID) {}

	FAttackTarget(uint32 targetActorID, int maxAttackers) : targetActorID(targetActorID), MAXATTACKERS(maxAttackers) {}

	// The ID of the actor being targeted by enemies
	uint32 targetActorID = 0;

	// The max number of attacker that can attack the target
	int MAXATTACKERS = 3;

	// Current number of attackers attacking the target
	int currNumOfAttackers = 0;

	FORCEINLINE bool CanAttack() { return currNumOfAttackers < MAXATTACKERS; }

	bool operator==(const FAttackTarget& attackTarget) const
	{
		return targetActorID == attackTarget.targetActorID;
	}
};

USTRUCT()
struct FEnemyAttacker
{
	GENERATED_USTRUCT_BODY()

	FEnemyAttacker() = default;

	FEnemyAttacker(TWeakObjectPtr<AEnemyCharacter> enemyAttacker) : enemy(enemyAttacker) 
	{
		controller = Cast<AEnemyAIController>(enemyAttacker->GetController());
		if (controller == nullptr)
			UE_LOG(LogTemp, Warning, TEXT("FEnemyAttacker FEnemyAttacker(): Failed to set enemy controller."));
	}

	FEnemyAttacker(TWeakObjectPtr<AEnemyCharacter> enemyAttacker, int targetIndex)
		: enemy(enemyAttacker), targetActorIndex(targetIndex) 
	{
		controller = Cast<AEnemyAIController>(enemyAttacker->GetController());
		if (controller == nullptr)
			UE_LOG(LogTemp, Warning, TEXT("FEnemyAttacker FEnemyAttacker(): Failed to set enemy controller."));
	}

	// The enemy attacker
	TWeakObjectPtr<AEnemyCharacter> enemy;

	// The enemy AI controller
	TWeakObjectPtr<AEnemyAIController> controller;

	// The index of the target attacker
	int targetActorIndex = -1;

	bool operator==(const FEnemyAttacker& enemyAttacker) const
	{
		return enemy == enemyAttacker.enemy;
	}
};

/**
 * A helper class that acts as a mediator between different
 * enemies when in combat.
 * 
 * TODO:
 * - OnTargetDeath implementation
 * - If an enemy can't attack a current target, check if there is any other targets to attack.
 * - A reset. Useful if the player leaves an combat area.
 */
UCLASS(Blueprintable)
class PROJECTINFESTATION_API ACombatManager : public AInfo
{
	GENERATED_BODY()
	
public: 
	/* Called at the beginning of play. */
	virtual void BeginPlay() override;

	/**
	 * Called when an attack target is found (delegate fired).
	 * @param originActor: Actor event was fired from.
	 * @param targetActor: Target actor.
	 */
	UFUNCTION(BlueprintCallable)
		void AttackTargetFound(AActor* originActor, AActor* targetActor);

	/**
	 * Called when an attack target is lost (delegate fired).
	 * @param originActor: Actor event was fired from.
	 * @param targetActor: Target actor.
	 */
	UFUNCTION(BlueprintCallable)
		void AttackTargetLost(AActor* originActor, AActor* targetActor);

	/**
	 * Called when an enemy actor dies (delegate fired).
	 * @param dyingActor: Enemy actor that died.
	 */
	UFUNCTION(BlueprintCallable)
		void OnEnemyDeath(AActor* dyingActor);

	/**
	 * Called when an target actor dies (delegate fired).
	 * NOTE: Not implemented, to be implemented when there are more than one target actor.
	 * @param dyingActor: Target actor that died.
	 */
	UFUNCTION(BlueprintCallable)
		void OnTargetDeath(AActor* dyingActor);

private:
	/**
	 * Removes actor from combat manager if it exists in the manager.
	 * @param enemyActor: Enemy actor to remove.
	 * @return If the removal was successful or not.
	 */
	bool RemoveEnemyActor(TWeakObjectPtr<AEnemyCharacter> enemyActor);

	/* Reference to game state(where events are declared). */ 
	TWeakObjectPtr<AInfestationGameState> gameState;

	/* List of attack targets. */
	TArray<struct FAttackTarget> attackTargets;

	/* List of enemy attackers currently attacking a target. */
	TMap<FGameplayTag, TArray<struct FEnemyAttacker>> enemiesInCombat;

	/* List of enemy attackers waiting to attack a target. */
	TMap<FGameplayTag, TArray<struct FEnemyAttacker>> enemiesInWaiting;
};
