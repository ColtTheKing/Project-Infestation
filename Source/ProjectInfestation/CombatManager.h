// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"

#include "InfestationGameState.h"

#include "CombatManager.generated.h"

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

	// ...
	UFUNCTION(BlueprintCallable)
		void OnEnemyDeath();

private:
	// Reference to game state (where events are declared). 
	TWeakObjectPtr<AInfestationGameState> gameState;
};
