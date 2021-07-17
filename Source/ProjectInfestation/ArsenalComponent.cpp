// Fill out your copyright notice in the Description page of Project Settings.

#include "ArsenalComponent.h"

// Sets default values for this component's properties
UArsenalComponent::UArsenalComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	activeWeapon = 0;
	grenadeActive = false;
}


// Called when the game starts
void UArsenalComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// Set up weapons
	for (FArsenalWeapon& weapon : weaponList)
	{
		weapon.ammoName = weapon.weaponSubclass.GetDefaultObject()->ammoName;
		weapon.clipSize = weapon.weaponSubclass.GetDefaultObject()->clipSize;
		weapon.enabledForPlayer = weapon.weaponSubclass.GetDefaultObject()->enabledForPlayer;

		weapon.reserveAmmo = 0;
		weapon.ammoInClip = weapon.clipSize;

		UE_LOG(LogTemp, Warning, TEXT("Clip Size %d"), weapon.clipSize);
	}

	// Set up grenade
	grenade.ammoName = grenade.weaponSubclass.GetDefaultObject()->ammoName;
	grenade.clipSize = grenade.weaponSubclass.GetDefaultObject()->clipSize;
	grenade.enabledForPlayer = grenade.weaponSubclass.GetDefaultObject()->enabledForPlayer;

	grenade.reserveAmmo = 0;
	grenade.ammoInClip = grenade.clipSize;
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

FArsenalWeapon UArsenalComponent::GetActiveWeapon()
{
	if (grenadeActive)
		return grenade;
	
	if (!weaponList.IsValidIndex(activeWeapon))
	{
		UE_LOG(LogTemp, Fatal, TEXT("Active weapon is not a valid index!"));
	}
	return weaponList[activeWeapon];
}

void UArsenalComponent::SetActiveWeaponInfo(int rAmmo, int cAmmo)
{
	if (grenadeActive)
	{
		grenade.reserveAmmo = rAmmo;
		grenade.ammoInClip = cAmmo;
	}
	else if (weaponList.IsValidIndex(activeWeapon))
	{
		weaponList[activeWeapon].reserveAmmo = rAmmo;
		weaponList[activeWeapon].ammoInClip = cAmmo;
	}
}

bool UArsenalComponent::ActivatePrevious()
{
	size_t currentActive = activeWeapon;

	if (currentActive < 1)
		currentActive = weaponList.Num() - 1;
	else
		currentActive--;

	if (!weaponList.IsValidIndex(currentActive))
		return false;

	//Keep cycling through weapons until you reach one that is enabled
	while (!weaponList[currentActive].enabledForPlayer)
	{
		if (currentActive < 1)
			currentActive = weaponList.Num() - 1;
		else
			currentActive--;

		if (!weaponList.IsValidIndex(currentActive))
			return false;
	}

	bool changedActive = weaponList.IsValidIndex(currentActive) && (currentActive != activeWeapon || grenadeActive);

	if (changedActive)
	{
		grenadeActive = false;
		activeWeapon = currentActive;
		return true;
	}

	return false;
}

bool UArsenalComponent::ActivateNext()
{
	size_t currentActive = activeWeapon;

	currentActive++;
	if (currentActive >= weaponList.Num())
		currentActive = 0;

	if (!weaponList.IsValidIndex(currentActive))
		return false;

	//Keep cycling through weapons until you reach one that is enabled
	while (!weaponList[currentActive].enabledForPlayer)
	{
		currentActive++;
		if (currentActive >= weaponList.Num())
			currentActive = 0;

		if (!weaponList.IsValidIndex(currentActive))
			return false;
	}

	bool changedActive = weaponList.IsValidIndex(currentActive) && (currentActive != activeWeapon || grenadeActive);

	if (changedActive)
	{
		grenadeActive = false;
		activeWeapon = currentActive;
		return true;
	}

	return false;
}

bool UArsenalComponent::ActivateIndex(size_t index)
{
	bool changedActive = weaponList.IsValidIndex(index) && (index != activeWeapon || grenadeActive);

	if (changedActive)
	{
		grenadeActive = false;
		activeWeapon = index;
		return true;
	}

	return false;
}

bool UArsenalComponent::ActivateGrenade()
{
	bool changedActive = grenade.enabledForPlayer && !grenadeActive;

	if (changedActive)
	{
		grenadeActive = true;
		return true;
	}

	return false;
}