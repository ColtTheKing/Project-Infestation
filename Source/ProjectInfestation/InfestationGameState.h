// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "InfestationGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerFoundSignature, AActor*, enemyActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathSignature);

/**
 * The game state for Project Infestation.
 * 
 * Keeps track of data relative to the current state of the game including 
 * timers, scores, winning team, etc. that all players in the game need to 
 * know about. Handles scripted events related to the state.
 * 
 * Exists on both the client and the server.
 */
UCLASS()
class PROJECTINFESTATION_API AInfestationGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	AInfestationGameState();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Events
	// NOTE: To be moved to separate EventList UObject class later.
	UPROPERTY(BlueprintAssignable)
		FOnPlayerFoundSignature onPlayerFoundDelegate;

	UPROPERTY(BlueprintAssignable)
		FOnDeathSignature onDeathDelegate;

};
