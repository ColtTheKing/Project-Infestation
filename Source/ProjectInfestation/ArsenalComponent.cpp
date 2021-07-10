// Fill out your copyright notice in the Description page of Project Settings.

#include "ArsenalComponent.h"

// Sets default values for this component's properties
UArsenalComponent::UArsenalComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UArsenalComponent::BeginPlay()
{
	Super::BeginPlay();

	if (weaponList.Num() == 0)
		UE_LOG(LogTemp, Error, TEXT("NO WEAPONS IN WEAPON LIST!!!"));

	for (size_t i = 0; i < weaponList.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("Added weapon"));
		weapons.Add(TSharedPtr<AGun>(Cast<AGun>(GetWorld()->SpawnActor(weaponList[i].weapon))));
	}

	activeWeapon = 0;
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
			if (!weapons.IsValidIndex(i))
			{
				UE_LOG(LogTemp, Warning, TEXT("Invalid index"));
				return;
			}
			if (!weapons[i].IsValid())
			{
				UE_LOG(LogTemp, Warning, TEXT("Invalid pointer"));
				return;
			}

			if (!weapons[i]->enabledForPlayer)
				weapons[i]->enabledForPlayer = true;

			weapons[i]->RestoreAmmo(numAmmo);
			break;
		}
	}
}

TSharedPtr<AGun> UArsenalComponent::GetActiveWeapon()
{
	if (weapons.IsValidIndex(activeWeapon))
	{
		return weapons[activeWeapon];
	}
	return TSharedPtr<AGun>(nullptr);
}

void UArsenalComponent::ActivatePrevious()
{
	activeWeapon--;
	if (activeWeapon < 0)
		activeWeapon = weapons.Num() - 1;

	if (!weapons.IsValidIndex(activeWeapon))
		return;

	//Keep cycling through weapons until you reach one that is enabled
	while (weapons[activeWeapon].Get()->enabledForPlayer)
	{
		activeWeapon--;
		if (activeWeapon < 0)
			activeWeapon = weapons.Num() - 1;

		if (!weapons.IsValidIndex(activeWeapon))
			return;
	}
}

void UArsenalComponent::ActivateNext()
{
	activeWeapon++;
	if (activeWeapon >= weapons.Num())
		activeWeapon = 0;

	if (!weapons.IsValidIndex(activeWeapon))
		return;

	//Keep cycling through weapons until you reach one that is enabled
	while (!weapons[activeWeapon].Get()->enabledForPlayer)
	{
		activeWeapon++;
		if (activeWeapon >= weapons.Num())
			activeWeapon = 0;

		if (!weapons.IsValidIndex(activeWeapon))
			return;
	}
}

void UArsenalComponent::ActivateIndex(size_t index)
{
	if (weapons.IsValidIndex(index))
		activeWeapon = index;
}