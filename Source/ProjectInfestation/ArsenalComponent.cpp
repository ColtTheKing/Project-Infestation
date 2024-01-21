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
	//for (AWeapon& weapon : weaponList)
	//{
	//	weapon.weaponName = weapon.weaponSubclass.GetDefaultObject()->ammoName;
	//	weapon.clipSize = weapon.weaponSubclass.GetDefaultObject()->clipSize;
	//	weapon.isEnabledWeapon = weapon.weaponSubclass.GetDefaultObject()->isEnabledWeapon;

	//	weapon.reserveAmmo = 0;
	//	weapon.ammoInClip = weapon.clipSize;

	//	UE_LOG(LogTemp, Warning, TEXT("Clip Size %d"), weapon.clipSize);
	//}

	//// Set up grenade
	//grenade.weaponName = grenade.weaponSubclass.GetDefaultObject()->ammoName;
	//grenade.clipSize = grenade.weaponSubclass.GetDefaultObject()->clipSize;
	//grenade.isEnabledWeapon = grenade.weaponSubclass.GetDefaultObject()->isEnabledWeapon;

	//grenade.reserveAmmo = 0;
	//grenade.ammoInClip = grenade.clipSize;
}


// Called every frame
void UArsenalComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UArsenalComponent::SetupWeapons(TArray<UChildActorComponent*> heldGuns, UChildActorComponent* heldGrenade, TArray<TSubclassOf<AGun>> gunTypes)
{
	for (size_t i = 0; i < heldGuns.Num(); i++)
	{
		heldGuns[i]->SetChildActorClass(gunTypes[i]);

		AActor* gunActor = heldGuns[i]->GetChildActor();
		AGun* myGun = Cast<AGun>(gunActor);

		gunList.Add(myGun);
	}

	/*gunList[activeWeapon]->SetReserveAmmo(rAmmo);
	gunList[activeWeapon]->SetAmmoInClip(cAmmo);*/
}

void UArsenalComponent::AddAmmo(FName gunName, int numAmmo)
{
	for (size_t i = 0; i < gunList.Num(); i++)
	{
		if (gunName.Compare(gunList[i]->weaponName) == 0)
		{
			if (!gunList[i]->isEnabledWeapon)
			{
				gunList[i]->isEnabledWeapon = true;

				//Add ammo to the clip first if this is the first ammo for this weapon
				int excess = numAmmo - gunList[i]->clipSize;
				
				if (excess > 0)
				{
					gunList[i]->SetReserveAmmo(excess);
					gunList[i]->SetAmmoInClip(gunList[i]->clipSize);
				}
				else
				{
					gunList[i]->SetAmmoInClip(numAmmo);
				}
			}
			else
			{
				gunList[i]->SetReserveAmmo(gunList[i]->GetReserveAmmo() + numAmmo);
			}

			break;
		}
	}
}

AWeapon* UArsenalComponent::GetActiveWeapon()
{
	if (grenadeActive)
		return grenade;
	
	if (!gunList.IsValidIndex(activeWeapon))
	{
		UE_LOG(LogTemp, Warning, TEXT("Active weapon is not a valid index!"));
		return nullptr;
	}
	return gunList[activeWeapon];
}

AWeapon* UArsenalComponent::GetWeaponOfType(FName gunName)
{
	for (int i = 0; i < gunList.Num(); i++)
	{
		if (gunName.Compare(gunList[i]->weaponName) == 0)
			return gunList[i];
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Weapon name does not match any weapons in the arsenal!"));
	return nullptr;
}

//void UArsenalComponent::SetActiveWeaponInfo(int rAmmo, int cAmmo)
//{
//	if (grenadeActive)
//	{
//		grenade.reserveAmmo = rAmmo;
//		grenade.ammoInClip = cAmmo;
//	}
//	else if (weaponList.IsValidIndex(activeWeapon))
//	{
//		weaponList[activeWeapon].reserveAmmo = rAmmo;
//		weaponList[activeWeapon].ammoInClip = cAmmo;
//	}
//	else
//	{
//		UE_LOG(LogTemp, Warning, TEXT("Active weapon is not a valid index!"));
//	}
//}

bool UArsenalComponent::ActivatePrevious()
{
	size_t currentActive = activeWeapon;

	if (currentActive < 1)
		currentActive = gunList.Num() - 1;
	else
		currentActive--;

	if (!gunList.IsValidIndex(currentActive))
		return false;

	//UNCOMMENT ONCE I ADD A WAY TO DISABLE WEAPONS WITH NEW SYSTEM
	
	////Keep cycling through weapons until you reach one that is enabled
	//while (!gunList[currentActive].isEnabledWeapon)
	//{
	//	if (currentActive < 1)
	//		currentActive = weaponList.Num() - 1;
	//	else
	//		currentActive--;

	//	if (!weaponList.IsValidIndex(currentActive))
	//		return false;
	//}

	bool changedActive = gunList.IsValidIndex(currentActive) && (currentActive != activeWeapon || grenadeActive);

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
	if (currentActive >= gunList.Num())
		currentActive = 0;

	if (!gunList.IsValidIndex(currentActive))
		return false;

	//UNCOMMENT ONCE I ADD A WAY TO DISABLE WEAPONS WITH NEW SYSTEM

	////Keep cycling through weapons until you reach one that is enabled
	//while (!weaponList[currentActive].isEnabledWeapon)
	//{
	//	currentActive++;
	//	if (currentActive >= weaponList.Num())
	//		currentActive = 0;

	//	if (!weaponList.IsValidIndex(currentActive))
	//		return false;
	//}

	bool changedActive = gunList.IsValidIndex(currentActive) && (currentActive != activeWeapon || grenadeActive);

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
	bool changedActive = gunList.IsValidIndex(index) && (index != activeWeapon || grenadeActive);

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
	//UNCOMMENT ONCE I ADD A WAY TO DISABLE WEAPONS WITH NEW SYSTEM

	//bool changedActive = grenade.isEnabledWeapon && !grenadeActive;
	bool changedActive = !grenadeActive;

	if (changedActive)
	{
		grenadeActive = true;
		return true;
	}

	return false;
}