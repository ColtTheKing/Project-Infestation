// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Engine/StaticMesh.h"
#include "Grenade.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTINFESTATION_API AGrenade : public AWeapon
{
	GENERATED_BODY()

public:
	// Blueprint to spawn when throwing an grenade.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		TSubclassOf<AActor> grenadeBP;

	// Mesh that player will hold when grenade is chosen.
	UPROPERTY(EditAnywhere, Category = "Mesh")
		UStaticMesh* grenadeMesh;

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
	UPROPERTY(EditAnywhere, Category = "Logic")
		float throwStrength;

	// Handle throwing logic
	UFUNCTION(BlueprintCallable, Category = "Action")
		void ThrowGrenade();

};
