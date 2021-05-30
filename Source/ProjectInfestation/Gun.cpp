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

	ammoInClip = clipSize;
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::RestoreAmmo(int ammo)
{
	reserveAmmo += ammo;

	UE_LOG(LogTemp, Warning, TEXT("Reserve Ammo After Restore: %d"), reserveAmmo);
}

void AGun::ConsumeAmmo(int ammo)
{
	if (ammoInClip >= ammo)
		ammoInClip -= ammo;

	UE_LOG(LogTemp, Warning, TEXT("Clip After Consumption: %d / %d"), ammoInClip, clipSize);
}

bool AGun::ClipHasAmmo(int ammo)
{
	if (ammoInClip >= ammo)
		return true;
	return false;
}

bool AGun::ClipCanReload()
{
	if (ammoInClip == clipSize || reserveAmmo == 0)
		return false;
	return true;
}

void AGun::ReloadClip()
{
	//Don't bother reloading if the clip is full or there is no more reserve ammo
	if (ammoInClip != clipSize && reserveAmmo != 0)
	{
		int neededAmmo = clipSize - ammoInClip;

		if (neededAmmo > reserveAmmo)
		{
			ammoInClip += reserveAmmo;
			reserveAmmo = 0;
		}
		else
		{
			reserveAmmo -= neededAmmo;
			ammoInClip = clipSize;
		}

		UE_LOG(LogTemp, Warning, TEXT("Reserve Ammo After Reload: %d"), reserveAmmo);
	}
}