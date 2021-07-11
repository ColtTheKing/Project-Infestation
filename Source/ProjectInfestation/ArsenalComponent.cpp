// Fill out your copyright notice in the Description page of Project Settings.

#include "ArsenalComponent.h"

// Sets default values for this component's properties
UArsenalComponent::UArsenalComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	activeWeapon = 0;
}


// Called when the game starts
void UArsenalComponent::BeginPlay()
{
	Super::BeginPlay();
	
	for (FWeapon& weapon : weaponList)
	{
		weapon.ammoName = weapon.gunSubclass.GetDefaultObject()->ammoName;
		weapon.clipSize = weapon.gunSubclass.GetDefaultObject()->clipSize;
		weapon.enabledForPlayer = weapon.gunSubclass.GetDefaultObject()->enabledForPlayer;

		weapon.reserveAmmo = 0;
		weapon.ammoInClip = weapon.clipSize;

		UE_LOG(LogTemp, Warning, TEXT("Clip Size %d"), weapon.clipSize);
	}
}


// Called every frame
void UArsenalComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UArsenalComponent::AddAmmo(FName ammoType, int numAmmo)
{
	for (size_t i = 0; i < weaponList.Num(); i++)
	{
		if (ammoType.Compare(weaponList[i].ammoName) == 0)
		{
			if (!weaponList[i].enabledForPlayer)
			{
				weaponList[i].enabledForPlayer = true;

				//Add ammo to the clip first if this is the first ammo for this weapon
				int excess = numAmmo - weaponList[i].clipSize;
				
				if (excess > 0)
				{
					weaponList[i].reserveAmmo = excess;
					weaponList[i].ammoInClip = weaponList[i].clipSize;
				}
				else
				{
					weaponList[i].ammoInClip = numAmmo;
				}
			}
			else
			{
				weaponList[i].reserveAmmo += numAmmo;
			}

			break;
		}
	}
}

FWeapon UArsenalComponent::GetActiveWeapon()
{
	if (!weaponList.IsValidIndex(activeWeapon))
	{
		UE_LOG(LogTemp, Fatal, TEXT("Active weapon is not a valid index!"));
	}
	return weaponList[activeWeapon];
}

void UArsenalComponent::ActivatePrevious()
{
	if (activeWeapon < 1)
		activeWeapon = weaponList.Num() - 1;
	else
		activeWeapon--;

	if (!weaponList.IsValidIndex(activeWeapon))
		return;

	//Keep cycling through weapons until you reach one that is enabled
	while (!weaponList[activeWeapon].enabledForPlayer)
	{
		if (activeWeapon < 1)
			activeWeapon = weaponList.Num() - 1;
		else
			activeWeapon--;

		if (!weaponList.IsValidIndex(activeWeapon))
			return;
	}
}

void UArsenalComponent::ActivateNext()
{
	activeWeapon++;
	if (activeWeapon >= weaponList.Num())
		activeWeapon = 0;

	if (!weaponList.IsValidIndex(activeWeapon))
		return;

	//Keep cycling through weapons until you reach one that is enabled
	while (!weaponList[activeWeapon].enabledForPlayer)
	{
		activeWeapon++;
		if (activeWeapon >= weaponList.Num())
			activeWeapon = 0;

		if (!weaponList.IsValidIndex(activeWeapon))
			return;
	}
}

void UArsenalComponent::ActivateIndex(size_t index)
{
	if (weaponList.IsValidIndex(index))
		activeWeapon = index;
}