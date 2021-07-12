// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Gun.h"
#include "Templates/SharedPointer.h"

#include "ArsenalComponent.generated.h"

USTRUCT()
struct FWeapon
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, Category = Class)
		TSubclassOf<AGun> gunSubclass;

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

	FWeapon GetActiveWeapon();

	void ActivatePrevious();
	void ActivateNext();
	void ActivateIndex(size_t index);
	void ActivateGrenade();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = Arsenal)
		TArray<FWeapon> weaponList;
	UPROPERTY(EditDefaultsOnly, Category = Arsenal)
		FWeapon grenade;

	size_t activeWeapon;
	bool grenadeActive;
};