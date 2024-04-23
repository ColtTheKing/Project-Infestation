// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "InfestationGameState.h"
#include "EnemyCharacter.h"
#include "CombatManager.generated.h"

USTRUCT()
struct FCombatGroup
{
	GENERATED_USTRUCT_BODY()

	FCombatGroup() = default;

	FCombatGroup(TWeakObjectPtr<AActor> targetActor) : targetActor(targetActor) {}

	// The actor being targeted by the enemies
	TWeakObjectPtr<AActor> targetActor;

	// Enemies attacking the target
	TMap<FString, TArray<TWeakObjectPtr<AEnemyCharacter>>> enemiesInCombat;

	// Enemies waiting to attack the target
	TMap<FString, TArray<TWeakObjectPtr<AEnemyCharacter>>> enemiesInWaiting;
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

	// A collection of groups of actors in combat
	TArray<struct FCombatGroup> groupsInCombat;
};
