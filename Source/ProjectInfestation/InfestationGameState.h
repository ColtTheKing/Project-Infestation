// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "InfestationDelegates.h"
#include "InfestationGameState.generated.h"

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

	// Gets the delegates storage object.
	FORCEINLINE TObjectPtr<UInfestationDelegates> GetDelegates() { return delegates; };

private:
	// Storage object that contains all game's delegates
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess))
		TObjectPtr<UInfestationDelegates> delegates;
};
