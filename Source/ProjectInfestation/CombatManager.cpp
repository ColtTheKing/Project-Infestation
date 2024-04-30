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
	gameState->GetDelegates()->onDeathDelegate.AddUniqueDynamic(this, &ACombatManager::OnEnemyDeath);
}

void ACombatManager::AttackTargetFound(AActor* originActor, AActor* targetActor)
{
	//// Check if originActor is of class enemyActor
	//TWeakObjectPtr<AEnemyCharacter> enemy = Cast<AEnemyCharacter>(originActor);
	//if (enemy == nullptr)
	//	return;

	//// Check if the target actor is already added to combat manager
	//FCombatGroup* currentCombatGroup = nullptr;
	//for (FCombatGroup &combatGroup : groupsInCombat)
	//{
	//	if (combatGroup.targetActor == TWeakObjectPtr(targetActor))
	//	{
	//		currentCombatGroup = &combatGroup;
	//		break;
	//	}
	//}

	//// Add target actor to combat manager if it wasn't found
	//if (currentCombatGroup == nullptr)
	//{
	//	groupsInCombat.Emplace(targetActor);
	//	currentCombatGroup = &groupsInCombat.Last();
	//}

	////// Get the type of the enemy
	//// Option 1:
	//FString enemyType;
	//for (auto tag : enemy->GetGameplayTags())
	//{
	//	if (tag.ToString().Contains("Enemy"))
	//	{
	//		enemyType = tag.ToString();
	//		break;
	//	}
	//}

	////// Option 2:
	////// Rather than defining gameplay tags in the config file, define them in the C++. That way you can easily check
	////// if a gameplay tag is in a container. 
	////// https://forums.unrealengine.com/t/using-gameplay-tags-in-c/106459/15
	////// ...

	//// Add enemy type to group if it doesn't exist
	//if (!currentCombatGroup->enemiesInCombat.Contains(enemyType))
	//{
	//	currentCombatGroup->enemiesInCombat.Add(enemyType);
	//	currentCombatGroup->enemiesInWaiting.Add(enemyType);
	//}

	//// Run logic for if the enemy can attack or has to wait to attack
	//// Note: Hardcoded for now, should be moved.
	//unsigned int const MAXATTACKERS = 3;
	//if (currentCombatGroup->enemiesInCombat[enemyType].Num() < MAXATTACKERS)
	//{
	//	// Able to attack
	//	currentCombatGroup->enemiesInCombat[enemyType].Add(enemy);
	//}
	//else
	//{
	//	// Unable to attack
	//	currentCombatGroup->enemiesInWaiting[enemyType].Add(enemy);
	//}
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
