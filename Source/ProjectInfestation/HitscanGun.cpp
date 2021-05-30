// Fill out your copyright notice in the Description page of Project Settings.


#include "HitscanGun.h"

AHitscanGun::AHitscanGun() : AGun() {}

void AHitscanGun::FireGun(AActor* actor)
{
	if (ClipHasAmmo(1))
	{
		ConsumeAmmo(1);

		FHitResult hit = ShootRay(actor, 10000000000, 0, 0);

		AEnemyCharacter* hitActor = Cast<AEnemyCharacter>(hit.Actor);

		if (hitActor)
		{
			UE_LOG(LogTemp, Warning, TEXT("Shot enemy"));

			hitActor->TakeDamage(damagePerPellet);
		}
	}
}

FHitResult AHitscanGun::ShootRay(AActor* actor, float length, float angleFromCenter, float angleAround)
{
	FVector rayLocation;
	FRotator rayRotation;
	FVector endRay = FVector::ZeroVector;

	APlayerController* const playerController = GetWorld()->GetFirstPlayerController();
	if (playerController)
	{
		playerController->GetPlayerViewPoint(rayLocation, rayRotation);

		endRay = rayLocation + (rayRotation.Vector() * length);
	}

	//Params are a tag for debugging, whether to use complex collision, and which object to ignore
	FCollisionQueryParams rayParams(SCENE_QUERY_STAT(ShootRay), true, actor);
	FHitResult hit(ForceInit);
	GetWorld()->LineTraceSingleByChannel(hit, rayLocation, endRay, ECC_Visibility, rayParams);

	return hit;
}