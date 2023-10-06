// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyQueen.h"

AEnemyQueen::AEnemyQueen() : Super()
{

}

// Called when the game starts or when spawned
void AEnemyQueen::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemyQueen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float AEnemyQueen::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	//Could pass in a damage type later so the actor can respond differently

	health->TakeDamage(damage);
	
		UE_LOG(LogTemp, Warning, TEXT("Queen took %d damage, %d health remaining"), damage, health->GetCurrentHp());
	
		if (health->GetCurrentHp() <= 0)
			KillQueen();
}

//From UE4 project
//void AEnemyQueen::TakeDamage(int damage)
//{
//	//Could pass in a damage type later so the actor can respond differently
//
//	health->TakeDamage(damage);
//
//	UE_LOG(LogTemp, Warning, TEXT("Queen took %d damage, %d health remaining"), damage, health->GetCurrentHp());
//
//	if (health->GetCurrentHp() <= 0)
//		KillQueen();
//}
