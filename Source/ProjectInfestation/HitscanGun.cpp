// Fill out your copyright notice in the Description page of Project Settings.


#include "HitscanGun.h"

AHitscanGun::AHitscanGun() : AGun() {}

void AHitscanGun::FireGun(FVector bulletStart, FRotator gunRotation)
{
	//Will implement more logic for spread, multiple pellets, etc. later
	FHitResult rayHit = ShootRay(bulletStart, gunRotation);
	AEnemyCharacter* hitActor = Cast<AEnemyCharacter>(rayHit.Actor);

	UE_LOG(LogTemp, Warning, TEXT("Gun is firing. Start:(%f, %f, %f)"), bulletStart.X, bulletStart.Y, bulletStart.Z);
	FVector temp = rayHit.Actor.Get()->GetActorLocation();
	UE_LOG(LogTemp, Warning, TEXT("Object hit is at:(%f, %f, %f)"), temp.X, temp.Y, temp.Z);

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

FHitResult AHitscanGun::ShootRay(FVector rayLocation, FRotator rayRotation)
{
	UE_LOG(LogTemp, Warning, TEXT("Shooting ray. Rotation:(%f, %f, %f)"), rayRotation.Vector().X, rayRotation.Vector().Y, rayRotation.Vector().Z);

	//use a very long ray so it's "infinite" for all intents and purposes
	FVector endRay = rayLocation + (rayRotation.Vector() * 1000000000);

	//Params are name/tag, something the docs doesn't explain, and which actor to ignore
	FCollisionQueryParams rayParams(SCENE_QUERY_STAT(ShootRay), true, this);
	FHitResult hit(ForceInit);
	GetWorld()->LineTraceSingleByChannel(hit, rayLocation, endRay, ECC_Visibility, rayParams);

	return hit;
}