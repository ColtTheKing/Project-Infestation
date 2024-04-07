// Fill out your copyright notice in the Description page of Project Settings.

#include "InfestationGameState.h"

AInfestationGameState::AInfestationGameState() : Super()
{
	// Note: Set to true for testing delegate system.
	PrimaryActorTick.bCanEverTick = false;
}

void AInfestationGameState::Tick(float DeltaTime)
{
	onDeathDelegate.Broadcast();
}
