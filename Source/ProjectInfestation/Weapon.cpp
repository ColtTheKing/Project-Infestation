// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Add the gun mesh and disable collisions with it
	weaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));
	weaponMesh->SetupAttachment(RootComponent);
	weaponMesh->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::RestoreReserveAmmo(int ammo)
{
	reserveAmmo += ammo;

	UE_LOG(LogTemp, Warning, TEXT("Reserve Ammo After Restore: %d"), reserveAmmo);
}

int AWeapon::GetAmmoInClip()
{
	return ammoInClip;
}

int AWeapon::GetReserveAmmo()
{
	return reserveAmmo;
}

void AWeapon::SetAmmoInClip(int ammo)
{
	ammoInClip = ammo;
}

void AWeapon::SetReserveAmmo(int ammo)
{
	reserveAmmo = ammo;
}