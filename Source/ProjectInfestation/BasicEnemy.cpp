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
		if (enemySpawner.IsValid())
			enemySpawner->HandleEnemyDespawn();

		KillBasicEnemy();
	}
}

void ABasicEnemy::SetEnemySpawner(TWeakObjectPtr<AEnemySpawner> aEnemySpawner)
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
