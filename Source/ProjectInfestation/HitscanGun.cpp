// Fill out your copyright notice in the Description page of Project Settings.


#include "HitscanGun.h"

AHitscanGun::AHitscanGun() : AGun() {}

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