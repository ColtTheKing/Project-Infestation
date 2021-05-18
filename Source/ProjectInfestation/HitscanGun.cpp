// Fill out your copyright notice in the Description page of Project Settings.


#include "HitscanGun.h"

AHitscanGun::AHitscanGun() : AGun() {}

void AHitscanGun::FireGun(FHitResult rayHit)
{
	//Will implement more logic for spread, multiple pellets, etc. later

	AEnemyCharacter* hitActor = Cast<AEnemyCharacter>(rayHit.Actor);

	//FVector temp = rayHit.Actor.Get()->GetActorLocation();
	//UE_LOG(LogTemp, Warning, TEXT("Object hit is at:(%f, %f, %f)"), temp.X, temp.Y, temp.Z);

	if (hitActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit enemy"));

		UHealthComponent* hitHealth = hitActor->health;

		if (hitHealth)
		{
			hitHealth->TakeDamage(damagePerPellet);
		}
	}
}