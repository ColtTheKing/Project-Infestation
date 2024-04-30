// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatManager.h"

#include "GameplayTagsModule.h"

void ACombatManager::BeginPlay()
{
	// Get game state reference for events.
	gameState = Cast<AInfestationGameState>(GetWorld()->GetGameState());
	if (!gameState.IsValid())
		UE_LOG(LogTemp, Error, TEXT("CombatManger BeginPlay(): Failed to find InfestationGameState reference."));

	// Subscribe to events.
	gameState->GetDelegates()->onTargetFoundDelegate.AddUniqueDynamic(this, &ACombatManager::AttackTargetFound);
	gameState->GetDelegates()->onTargetLostDelegate.AddUniqueDynamic(this, &ACombatManager::AttackTargetLost);
	gameState->GetDelegates()->onEnemyDeathDelegate.AddDynamic(this, &ACombatManager::OnEnemyDeath);
	gameState->GetDelegates()->onTargetDeathDelegate.AddDynamic(this, &ACombatManager::OnTargetDeath);
}

void ACombatManager::AttackTargetFound(AActor* originActor, AActor* targetActor)
{
	// Check if originActor is of class enemyActor or enemy is already attacking
	TWeakObjectPtr<AEnemyCharacter> enemy = Cast<AEnemyCharacter>(originActor);
	if (enemy == nullptr || enemy->GetEnemyState() != FGameplayTag::RequestGameplayTag("Enemy.State.Passive"))
		return;

	// Check if the target actor is already added to combat manager
	FAttackTarget targetToFind(targetActor->GetUniqueID());
	int currentAttackTargetIndex = attackTargets.Find(targetToFind);

	// Add target actor to combat manager if it wasn't found
	if (currentAttackTargetIndex < 0)
	{
		attackTargets.Emplace(targetActor->GetUniqueID());
		currentAttackTargetIndex = attackTargets.Num() - 1;
	}

	// Add enemy type to group if it doesn't exist
	FGameplayTag enemyType = enemy->GetEnemyType();
	if (!enemiesInCombat.Contains(enemyType))
	{
		enemiesInCombat.Add(enemyType);
		enemiesInWaiting.Add(enemyType);
	}

	// Check if the enemy is already added to the combat manager and exit if it is
	FEnemyAttacker attackerToFind(enemy);
	if (enemiesInCombat[enemyType].Find(attackerToFind) > -1 || enemiesInWaiting[enemyType].Find(attackerToFind) > -1)
		return;

	// Run logic for if the enemy can attack or has to wait to attack
	if (attackTargets[currentAttackTargetIndex].CanAttack())
	{
		enemiesInCombat[enemyType].Emplace(enemy, currentAttackTargetIndex);
		attackTargets[currentAttackTargetIndex].currNumOfAttackers++;
		enemy->SetEnemyState(FGameplayTag::RequestGameplayTag("Enemy.State.Attacking")); // TO BE REPLACED
	}
	else
	{
		enemiesInWaiting[enemyType].Emplace(enemy);
		enemy->SetEnemyState(FGameplayTag::RequestGameplayTag("Enemy.State.Waiting")); // TO BE REPLACED
	}

	// Debug messages for testing
	/*FString test = TEXT("Number of Attacking Enemies: ");
	test.AppendInt(enemiesInCombat[enemyType].Num());
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, test);

	test = TEXT("Number of Waiting Enemies: ");
	test.AppendInt(enemiesInWaiting[enemyType].Num());
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, test);*/
}

void ACombatManager::AttackTargetLost(AActor* originActor, AActor* targetActor)
{
	// Check if originActor is of class enemyActor or if the enemy isn't attacking
	TWeakObjectPtr<AEnemyCharacter> enemy = Cast<AEnemyCharacter>(originActor);
	if (enemy == nullptr || enemy->GetEnemyState() == FGameplayTag::RequestGameplayTag("Enemy.State.Passive"))
		return;

	// Check if enemy type of the enemy exists in the combat manager
	FGameplayTag enemyType = enemy->GetEnemyType();
	if (!enemiesInCombat.Contains(enemyType) && !enemiesInWaiting.Contains(enemyType))
		return;

	// Run Logic for if the enemy is attacking or waiting
	FEnemyAttacker enemyAttacker(enemy);
	if (enemy->GetEnemyState() == FGameplayTag::RequestGameplayTag("Enemy.State.Attacking"))
	{
		// Get index and check if it exists in the combat manager
		int enemyAttackerIndex = enemiesInCombat[enemyType].Find(enemyAttacker);
		if (enemyAttackerIndex < 0)
			return;

		// Remove from list of attackers
		int attackTargetIndex = enemiesInCombat[enemyType][enemyAttackerIndex].targetActorIndex;
		enemiesInCombat[enemyType].RemoveAtSwap(enemyAttackerIndex);
		attackTargets[attackTargetIndex].currNumOfAttackers--;

		// Add new attacker from list of enemies' waiting
		if (!enemiesInWaiting[enemyType].IsEmpty())
		{
			// Get attacker in waiting
			FEnemyAttacker attackerInWaiting = enemiesInWaiting[enemyType][0];
			attackerInWaiting.enemy->SetEnemyState(FGameplayTag::RequestGameplayTag("Enemy.State.Attacking")); // TO BE REPLACED
			attackerInWaiting.targetActorIndex = attackTargetIndex;

			// Update lists
			enemiesInCombat[enemyType].Add(attackerInWaiting);
			attackTargets[attackTargetIndex].currNumOfAttackers++;
			enemiesInWaiting[enemyType].RemoveAtSwap(0);
		}

		// Update enemy state
		enemy->SetEnemyState(FGameplayTag::RequestGameplayTag("Enemy.State.Passive")); // TO BE REPLACED
	}
	else if (enemy->GetEnemyState() == FGameplayTag::RequestGameplayTag("Enemy.State.Waiting"))
	{
		// Get index and check if it exists in the combat manager
		int enemyAttackerIndex = enemiesInWaiting[enemyType].Find(enemyAttacker);
		if (enemyAttackerIndex < 0)
			return;

		// Remove from list of attackers
		enemiesInWaiting[enemyType].RemoveAtSwap(enemyAttackerIndex);

		// Update enemy state
		enemy->SetEnemyState(FGameplayTag::RequestGameplayTag("Enemy.State.Passive")); // TO BE REPLACED
	}
	
}

void ACombatManager::OnEnemyDeath(AActor* dyingActor)
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("OnEnemyDeath(): Event Fired"));
}

void ACombatManager::OnTargetDeath(AActor* dyingActor)
{
	// ...
}
