// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicEnemy.h"

#include "EnemySpawner.h"

ABasicEnemy::ABasicEnemy() : Super()
{

}

void ABasicEnemy::TakeDamage(int damage)
{
	//Could pass in a damage type later so the actor can respond differently

	health->TakeDamage(damage);

	UE_LOG(LogTemp, Warning, TEXT("Enemy took %d damage, %d health remaining"), damage, health->GetCurrentHp());

	if (health->GetCurrentHp() <= 0)
	{
		// TODO: Always assumes that the enemy type tag is in the second position
		if (IsValid(enemySpawner)) {
			FName enemyToRespawnTag = this->Tags[1];
			enemySpawner->AddEnemyToRespawnQueue(enemyToRespawnTag);
		}

		Destroy();
	}
}

void ABasicEnemy::SetEnemySpawner(AEnemySpawner* aEnemySpawner)
{
	enemySpawner = aEnemySpawner;
}

// Called every frame
void ABasicEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABasicEnemy::BeginPlay()
{
	Super::BeginPlay();
}
