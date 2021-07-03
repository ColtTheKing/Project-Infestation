// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/Character.h"
#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
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
	float timePlayed;

public:

	// Default constructor
	AInfestationGameMode() {};

	// Called before any other scripts (including PreInitializeComponents)
	void InitGame(const FString& mapName, const FString& options, FString& errorMessage) override;

	// Level logic
	UPROPERTY(BlueprintReadWrite)
		bool gameEnded;

	UFUNCTION(BlueprintCallable)
		void RestartGame();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void WinGame();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void LoseGame();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void PauseGame();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void UnpauseGame();
};
