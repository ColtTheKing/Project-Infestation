// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatManager.h"

void ACombatManager::BeginPlay()
{
	gameState = Cast<AInfestationGameState>(GetWorld()->GetGameState());
	if (!gameState.IsValid())
		UE_LOG(LogTemp, Error, TEXT("CombatManger BeginPlay(): Failed to find InfestationGameState reference."));
}
