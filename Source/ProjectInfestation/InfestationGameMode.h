// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "InfestationGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTINFESTATION_API AInfestationGameMode : public AGameModeBase
{
private:

	GENERATED_BODY()

	// Class variables
	// TODO: Add map variable
	float timePlayed;

public:

	// Default constructor
	AInfestationGameMode() {};

	// Called before any other scripts (including PreInitializeComponents)
	void InitGame(const FString& mapName, const FString& options, FString& errorMessage) override;

	// Level logic
};
