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
}


// Called every frame
void UArsenalComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UArsenalComponent::SetupWeapons(UPrimitiveComponent* attachTo)
{
	FTransform localToWorld = FTransform(attachTo->GetComponentLocation());
	FVector location = localToWorld.GetLocation();
	FRotator rotation = FRotator(localToWorld.GetRotation());

	for (size_t i = 0; i < gunBPs.Num(); i++)
	{
		AActor* gunActor = GetWorld()->SpawnActor(gunBPs[i], &location, &rotation);
		gunActor->AttachToComponent(attachTo, FAttachmentTransformRules::KeepRelativeTransform);

		AGun* myGun = Cast<AGun>(gunActor);
		gunList.Add(myGun);
	}

	AActor* grenadeActor = GetWorld()->SpawnActor(grenadeBP, &location, &rotation);
	grenadeActor->AttachToComponent(attachTo, FAttachmentTransformRules::KeepRelativeTransform);

	grenade = Cast<AWeapon>(grenadeActor);

	//Make sure the first weapon in the arsenal is the only one active (visible and usable)
	EnableActiveWeapon(0);

	/*gunList[activeWeapon]->SetReserveAmmo(gunList[activeWeapon]->clipSize);
	gunList[activeWeapon]->SetAmmoInClip(gunList[activeWeapon]->clipSize);*/
}

void UArsenalComponent::SetWeaponEnabled(int index, bool enabled)
{
	UStaticMeshComponent* staticMesh = gunList[index]->GetComponentByClass<UStaticMeshComponent>();
	//enabled ? staticMesh->Activate() : staticMesh->Deactivate();
	staticMesh->SetVisibility(enabled);
	staticMesh->SetComponentTickEnabled(enabled);
}

void UArsenalComponent::SetGrenadeEnabled(bool enabled)
{
	UStaticMeshComponent* staticMesh = grenade->GetComponentByClass<UStaticMeshComponent>();
	//enabled ? staticMesh->Activate() : staticMesh->Deactivate();
	staticMesh->SetVisibility(enabled);
	staticMesh->SetComponentTickEnabled(enabled);
}

void UArsenalComponent::AddAmmo(FName gunName, int numAmmo)
{
	for (size_t i = 0; i < gunList.Num(); i++)
	{
		if (gunName.Compare(gunList[i]->weaponName) == 0)
		{
			if (!gunList[i]->playerCanUse)
			{
				gunList[i]->playerCanUse = true;

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

bool UArsenalComponent::ActivatePrevious()
{
	size_t currentActive = activeWeapon;

	if (grenadeActive)
		; //If grenade is currently active, just use the previously active weapon
	else if (currentActive < 1)
		currentActive = gunList.Num() - 1;
	else
		currentActive--;

	if (!gunList.IsValidIndex(currentActive))
		return false;

	//UNCOMMENT ONCE I ADD A WAY TO DISABLE WEAPONS WITH NEW SYSTEM
	
	////Keep cycling through weapons until you reach one that is enabled
	//while (!gunList[currentActive].playerCanUse)
	//{
	//	if (currentActive < 1)
	//		currentActive = weaponList.Num() - 1;
	//	else
	//		currentActive--;

	//	if (!weaponList.IsValidIndex(currentActive))
	//		return false;
	//}

	//If the weapon is actually different than before
	bool changedActive = (currentActive != activeWeapon) || grenadeActive;
	if (changedActive)
		return EnableActiveWeapon(changedActive);

	return false;
}

bool UArsenalComponent::ActivateNext()
{
	size_t currentActive = activeWeapon;

	if (grenadeActive)
		; //If grenade is currently active, just use the previously active weapon
	else if (currentActive >= gunList.Num() - 1)
		currentActive = 0;
	else
		currentActive++;

	if (!gunList.IsValidIndex(currentActive))
		return false;

	//UNCOMMENT ONCE I ADD A WAY TO DISABLE WEAPONS WITH NEW SYSTEM

	////Keep cycling through weapons until you reach one that is enabled
	//while (!weaponList[currentActive].playerCanUse)
	//{
	//	currentActive++;
	//	if (currentActive >= weaponList.Num())
	//		currentActive = 0;

	//	if (!weaponList.IsValidIndex(currentActive))
	//		return false;
	//}

	//If the weapon is actually different than before
	bool changedActive = (currentActive != activeWeapon) || grenadeActive;
	if (changedActive)
		return EnableActiveWeapon(changedActive);

	return false;
}

bool UArsenalComponent::ActivateIndex(size_t index)
{
	//HAVE CODE HERE LATER TO DEAL WITH DISABLED WEAPONS ONCE THAT IS A THING

	if (!gunList.IsValidIndex(index))
		return false;

	//If the weapon is actually different than before
	bool changedActive = (index != activeWeapon) || grenadeActive;
	if (changedActive)
		return EnableActiveWeapon(changedActive);

	return false;
}

bool UArsenalComponent::ActivateWeaponOfType(FName gunName)
{
	/*UE_LOG(LogTemp, Warning, TEXT("Weapon name does not match any weapons in the arsenal!"));
	return nullptr;*/

	//Switch to grenade if that's the weapon type
	if (gunName == grenade->weaponName)
		return ActivateAndEnableGrenade();

	//Find the gun with the provided name in the gun list
	//HAVE CODE HERE LATER TO DEAL WITH FAILING TO SWITCH IF THAT WEAPON IS DISABLED
	int gunIndex = -1;
	for (int i = 0; i < gunList.Num(); i++)
	{
		if (gunName.Compare(gunList[i]->weaponName) == 0)
		{
			gunIndex = i;
			break;
		}
	}

	if (gunIndex == -1)
		return false;

	bool changedActive = (gunIndex != activeWeapon) || grenadeActive;

	if (changedActive)
		return EnableActiveWeapon(gunIndex);

	return false;
}

bool UArsenalComponent::ActivateAndEnableGrenade()
{
	//UNCOMMENT ONCE I ADD A WAY TO DISABLE WEAPONS WITH NEW SYSTEM
	//bool changedActive = grenade.playerCanUse && !grenadeActive;
	bool changedActive = !grenadeActive;

	if (changedActive)
	{
		grenadeActive = true;



		//DISABLE ALL NON GRENADE WEAPONS AND ENABLE GRENADE




		return true;
	}

	return false;
}

//Sets which weapon is visible and usable
bool UArsenalComponent::EnableActiveWeapon(int weaponIndex)
{
	grenadeActive = false;
	activeWeapon = weaponIndex;

	//ENABLE WEAPON AT INDEX AND DISABLE ALL OTHERS
	for (int i = 0; i < gunList.Num(); i++)
	{
		SetWeaponEnabled()
	}
}