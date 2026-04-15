// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Engine/StaticMesh.h"
#include "Grenade.generated.h"

/*
	Unknown if the struct is needed but it could be useful for switching grenade 
	types later in development. Going to leave it for now.
*/
USTRUCT()
struct FHeldGrenade
{
	GENERATED_USTRUCT_BODY()

	// Grenade actor to spawn when using grenade
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> grenadeBP;
};

/**
 * 
 */
UCLASS()
class PROJECTINFESTATION_API AGrenade : public AWeapon
{
	GENERATED_BODY()

public:
	// Currently held grenade
	UPROPERTY(EditAnywhere, Category = "Grenade")
		FHeldGrenade heldGrenade;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Grenade")
		UStaticMeshComponent* spawnPosition;

	// Sets default values for this actor's properties
	AGrenade();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Attack")
		void UseWeapon(AActor* actor) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Attack")
		void StopUsingWeapon() override;

	void ConsumeAmmo(int ammo) override;

protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Grenade")
		float throwStrength;

	// Handle throwing logic
	UFUNCTION(BlueprintCallable, Category = "Action")
		void ThrowGrenade();

};
