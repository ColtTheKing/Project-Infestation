// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Grenade.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTINFESTATION_API AGrenade : public AWeapon
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGrenade();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Attack")
		void UseWeapon(AActor* actor) override;

	void ConsumeAmmo(int ammo) override;

protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;

private:

	// Handle throwing logic
	void ThrowGrenade();

};
