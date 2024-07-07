// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatArea.h"

// Sets default values
ACombatArea::ACombatArea()
{

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACombatArea::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACombatArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

