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
	gameState->GetDelegates()->onDeathDelegate.AddDynamic(this, &ACombatManager::OnEnemyDeath);
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
	FEnemyAttacker attackerToFind(enemy->GetUniqueID());
	if (enemiesInCombat[enemyType].Find(attackerToFind) > -1 || enemiesInWaiting[enemyType].Find(attackerToFind) > -1)
		return;

	// Run logic for if the enemy can attack or has to wait to attack
	if (attackTargets[currentAttackTargetIndex].CanAttack())
	{
		enemiesInCombat[enemyType].Emplace(enemy->GetUniqueID(), currentAttackTargetIndex);
		attackTargets[currentAttackTargetIndex].currNumOfAttackers++;
		enemy->SetEnemyState(FGameplayTag::RequestGameplayTag("Enemy.State.Attacking")); // TO BE REPLACED
	}
	else
	{
		enemiesInWaiting[enemyType].Emplace(enemy->GetUniqueID());
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
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("CombatManger AttackTargetLost(): Event Fired"));
}

void ACombatManager::OnEnemyDeath()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("CombatManger OnEnemyDeath(): Event Fired"));
}
