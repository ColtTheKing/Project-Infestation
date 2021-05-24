// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::RestoreAmmo(int ammo)
{
	UE_LOG(LogTemp, Warning, TEXT("Current Ammo Before Reload: %d"), currentAmmo);
	
	if (clipSize < (ammo + currentAmmo))
		currentAmmo = clipSize;
	else
		currentAmmo += ammo;

	UE_LOG(LogTemp, Warning, TEXT("Current Ammo After Reload: %d"), currentAmmo);
}
