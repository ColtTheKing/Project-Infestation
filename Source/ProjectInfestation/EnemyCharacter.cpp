// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyCharacter.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter() : Super()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	currentState = FGameplayTag::RequestGameplayTag("Enemy.State.Passive");
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Set up collision
	
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemyCharacter::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	TagContainer.AddTag(enemyType);
	TagContainer.AddTag(currentState);
}
