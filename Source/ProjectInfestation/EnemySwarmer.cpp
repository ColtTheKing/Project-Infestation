// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySwarmer.h"

// Sets default values
AEnemySwarmer::AEnemySwarmer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemySwarmer::BeginPlay()
{
	Super::BeginPlay();
	
	// Set up collision
	// TODO: Change so that collision is mapped to specific attack, not just the character's model 
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemySwarmer::OnOverlapBegin);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AEnemySwarmer::OnOverlapEnd);
}

// Called every frame
void AEnemySwarmer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemySwarmer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemySwarmer::TakeDamage(float damageTaken)
{
}

void AEnemySwarmer::OnOverlapBegin(class UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void AEnemySwarmer::OnOverlapEnd(class UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

