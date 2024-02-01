// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Gun.h"
#include "Templates/SharedPointer.h"

#include "ArsenalComponent.generated.h"

USTRUCT()
struct FArsenalWeapon
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, Category = Class)
		TSubclassOf<AWeapon> weaponSubclass;

	FName weaponName;
	int reserveAmmo, ammoInClip, clipSize;
	bool isEnabledWeapon;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECTINFESTATION_API UArsenalComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UArsenalComponent();

	void SetupWeapons(UPrimitiveComponent* attachTo);
	void SetWeaponEnabled(int index, bool enabled);
	void SetGrenadeEnabled(bool enabled);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddAmmo(FName gunName, int numAmmo);

	AWeapon* GetActiveWeapon();

	UFUNCTION(BlueprintCallable, Category = Weapon)
		AWeapon* GetWeaponOfType(FName gunName); //Assuming this gets a reference that I can edit

	//These return true, if they activated a different weapon
	bool ActivatePrevious();
	bool ActivateNext();
	bool ActivateIndex(size_t index);
	bool ActivateAndEnableGrenade();
	bool ActivateWeaponOfType(FName gunName);
	bool EnableActiveWeapon(int weaponIndex);

	UPROPERTY(EditDefaultsOnly, Category = Arsenal)
		TArray<TSubclassOf<AGun>> gunBPs;

	UPROPERTY(EditDefaultsOnly, Category = Arsenal)
		TSubclassOf<AWeapon> grenadeBP;

	UPROPERTY(EditDefaultsOnly, Category = Arsenal)
		TArray<AGun*> gunList;

	UPROPERTY(EditDefaultsOnly, Category = Arsenal)
		AWeapon* grenade;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	size_t activeWeapon;
	bool grenadeActive;
};