// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class PROJECTINFESTATION_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gun)
		int clipSize;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gun)
		bool enabledForPlayer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gun)
		FName ammoName;

	// Sets default values for this actor's properties
	AWeapon();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void UseWeapon(AActor* actor) PURE_VIRTUAL(AWeapon::UseWeapon, ;);

	virtual void StopUsingWeapon() PURE_VIRTUAL(AWeapon::StopUsingWeapon, ;);

	void RestoreReserveAmmo(int ammo);

	UFUNCTION(BlueprintCallable, Category = Ammo)
		virtual void ConsumeAmmo(int ammo) PURE_VIRTUAL(AWeapon::ConsumeAmmo, ;);

	UFUNCTION(BlueprintCallable, Category = Attack)
		bool CanAttack();

	UFUNCTION(BlueprintCallable, Category = Attack)
		void ResetAttackCooldown();

	UFUNCTION(BlueprintCallable, Category = Ammo)
		int GetAmmoInClip();

	UFUNCTION(BlueprintCallable, Category = Ammo)
		int GetReserveAmmo();

	void SetAmmoInClip(int ammo);
	void SetReserveAmmo(int ammo);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Mesh)
		UStaticMeshComponent* weaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gun)
		float attackCooldown;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gun)
		int damagePerHit;

	int reserveAmmo, ammoInClip;

private:
	float timeUntilNextAttack;
};
