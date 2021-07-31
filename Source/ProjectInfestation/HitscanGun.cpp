// Fill out your copyright notice in the Description page of Project Settings.


#include "HitscanGun.h"

AHitscanGun::AHitscanGun() : Super() {}

// Called when the game starts or when spawned
void AHitscanGun::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AHitscanGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

		FVector shotDirection = CalculateShotSpread(rayRotation.Vector());

		endRay = rayLocation + (shotDirection * length);
	}

	//Params are a tag for debugging, whether to use complex collision, and which object to ignore
	FCollisionQueryParams rayParams(SCENE_QUERY_STAT(ShootRay), true, actor);
	FHitResult hit(ForceInit);
	GetWorld()->LineTraceSingleByChannel(hit, rayLocation, endRay, ECC_Visibility, rayParams);

	return hit;
}