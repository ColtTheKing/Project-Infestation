// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Add a mesh to keep track of where shots come out of the gun
	shotPosition = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shot Position"));
	shotPosition->SetupAttachment(weaponMesh);
	shotPosition->SetVisibility(false);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();

	ammoInClip = clipSize;

	UE_LOG(LogTemp, Warning, TEXT("Ammo In Clip At Start: %d"), ammoInClip);

}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::ConsumeAmmo(int ammo)
{
	if (ammoInClip >= ammo)
		ammoInClip -= ammo;

	UE_LOG(LogTemp, Warning, TEXT("Clip After Consumption: %d / %d"), ammoInClip, clipSize);
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
	if (ClipCanReload())
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