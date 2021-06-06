// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySwarmer.h"

AEnemySwarmer::AEnemySwarmer() : Super()
{

}

// Called when the game starts or when spawned
void AEnemySwarmer::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemySwarmer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemySwarmer::TakeDamage(int damage)
{
	//Could pass in a damage type later so the actor can respond differently

	health->TakeDamage(damage);

	UE_LOG(LogTemp, Warning, TEXT("Enemy took %d damage, %d health remaining"), damage, health->GetCurrentHp());

	if (health->GetCurrentHp() <= 0)
	{
		// TODO: Always assumes that the enemy type tag is in the second position
		FName enemyToRespawnTag = this->Tags[1];
		//enemySpawner->AddEnemyToRespawnQueue(enemyToRespawnTag);

		Destroy();
	}
}
