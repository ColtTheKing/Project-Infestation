// Fill out your copyright notice in the Description page of Project Settings.


#include "InfestationGameMode.h"

void AInfestationGameMode::InitGame(const FString& mapName, const FString& options, FString& errorMessage)
{
	// Call super class to init systems
	AGameModeBase::InitGame(mapName, options, errorMessage);

	// Generate map class
	// TODO: Call function from MapGenerator class to generate level map
}

void AInfestationGameMode::CompleteLevel()
{
}
