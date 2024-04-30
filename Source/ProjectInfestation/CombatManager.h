// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "InfestationGameState.h"
#include "EnemyCharacter.h"
#include "CombatManager.generated.h"

USTRUCT()
struct FAttackTarget
{
	GENERATED_USTRUCT_BODY()

	FAttackTarget() = default;

	FAttackTarget(uint32 targetActorID) : targetActorID(targetActorID) {}

	// The ID of the actor being targeted by enemies
	uint32 targetActorID = 0;

	// The max number of attacker that can attack the target
	unsigned int MAXATTACKERS = 3;

	// Current number of attackers attacking the target
	unsigned int currNumOfAttackers = 0;

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

	FEnemyAttacker(TWeakObjectPtr<AEnemyCharacter> enemyAttacker) : enemy(enemyAttacker) {}

	FEnemyAttacker(TWeakObjectPtr<AEnemyCharacter> enemyAttacker, int targetIndex)
		: enemy(enemyAttacker), targetActorIndex(targetIndex) {}

	// The enemy attacker
	TWeakObjectPtr<AEnemyCharacter> enemy;

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
	// Called at the beginning of play.
	virtual void BeginPlay() override;

	// Called when an attack target is found (delegate fired).
	UFUNCTION(BlueprintCallable)
		void AttackTargetFound(AActor* originActor, AActor* targetActor);
	
	// Called when an attack target is lost (delegate fired).
	UFUNCTION(BlueprintCallable)
		void AttackTargetLost(AActor* originActor, AActor* targetActor);

	// Called when an enemy actor dies.
	UFUNCTION(BlueprintCallable)
		void OnEnemyDeath(AActor* dyingActor);

	// Called when an target actor dies (delegate fired).
	// NOTE: Not implemented, to be implemented when there are more than one target actor.
	UFUNCTION(BlueprintCallable)
		void OnTargetDeath(AActor* dyingActor);

private:
	// Reference to game state (where events are declared). 
	TWeakObjectPtr<AInfestationGameState> gameState;

	// List of attack targets.
	TArray<struct FAttackTarget> attackTargets;

	// List of enemy attackers currently attacking a target.
	TMap<FGameplayTag, TArray<struct FEnemyAttacker>> enemiesInCombat;

	// List of enemy attackers waiting to attack a target.
	TMap<FGameplayTag, TArray<struct FEnemyAttacker>> enemiesInWaiting;
};
