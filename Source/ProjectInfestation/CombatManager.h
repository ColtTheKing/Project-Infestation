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
 */
UCLASS(Blueprintable)
class PROJECTINFESTATION_API ACombatManager : public AInfo
{
	GENERATED_BODY()
	
public: 
	// Called at the beginning of play.
	virtual void BeginPlay() override;

	// Called when an attack target is found (delegate fired)
	UFUNCTION(BlueprintCallable)
		void AttackTargetFound(AActor* originActor, AActor* targetActor);
	
	// Called when an attack target is lost (delegate fired)
	UFUNCTION(BlueprintCallable)
		void AttackTargetLost(AActor* originActor, AActor* targetActor);

	// ...
	UFUNCTION(BlueprintCallable)
		void OnEnemyDeath();

private:
	// Reference to game state (where events are declared). 
	TWeakObjectPtr<AInfestationGameState> gameState;

	//
	TArray<struct FAttackTarget> attackTargets;

	//
	TMap<FGameplayTag, TArray<struct FEnemyAttacker>> enemiesInCombat;

	//
	TMap<FGameplayTag, TArray<struct FEnemyAttacker>> enemiesInWaiting;
};
