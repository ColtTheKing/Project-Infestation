// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapon.h"
#include "Templates/SharedPointer.h"

#include "ArsenalComponent.generated.h"

USTRUCT()
struct FArsenalWeapon
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, Category = Class)
		TSubclassOf<AWeapon> weaponSubclass;

	FName ammoName;
	int reserveAmmo, ammoInClip, clipSize;
	bool enabledForPlayer;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECTINFESTATION_API UArsenalComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UArsenalComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddAmmo(FName ammoType, int numAmmo);

	FArsenalWeapon GetActiveWeapon();
	void SetActiveWeaponInfo(int rAmmo, int cAmmo);

	//These return true, if they activated a different weapon
	bool ActivatePrevious();
	bool ActivateNext();
	bool ActivateIndex(size_t index);
	bool ActivateGrenade();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = Arsenal)
		TArray<FArsenalWeapon> weaponList;

	UPROPERTY(EditDefaultsOnly, Category = Arsenal)
		FArsenalWeapon grenade;

	size_t activeWeapon;
	bool grenadeActive;
};