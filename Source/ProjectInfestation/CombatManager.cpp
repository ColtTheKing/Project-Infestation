// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatManager.h"

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
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("CombatManger AttackTargetFound(): Event Fired"));
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
