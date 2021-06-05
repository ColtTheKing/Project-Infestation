// Fill out your copyright notice in the Description page of Project Settings.


#include "InfestationGameMode.h"

void AInfestationGameMode::InitGame(const FString& mapName, const FString& options, FString& errorMessage)
{
	// Call super class to init systems
	AGameModeBase::InitGame(mapName, options, errorMessage);

	// Init Variables
	timePlayed = 0;
	playerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);

	// Generate map class
	// TODO: Call function from MapGenerator class to generate level map
}

void AInfestationGameMode::RestartGame()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void AInfestationGameMode::EndGame()
{
	UHealthComponent* playerHealth = playerCharacter->FindComponentByClass<UHealthComponent>();
	if (playerHealth->GetCurrentHp() <= 0)
	{
		// Load Game Over screen
	}
	else
	{
		// Load Victory screen
	}
}
