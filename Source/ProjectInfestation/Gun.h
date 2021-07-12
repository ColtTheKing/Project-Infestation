// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"

#include "Gun.generated.h"

UCLASS()
class PROJECTINFESTATION_API AGun : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Mesh)
		UStaticMeshComponent* gunMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gun)
		UStaticMeshComponent* shotPosition;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gun)
		int spreadAngle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gun)
		int pelletsPerShot;											

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gun)
		int ammoConsumedPerShot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gun)
		float fireRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gun)
		int clipSize;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gun)
		int damagePerPellet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gun)
		bool enabledForPlayer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gun)
		FName ammoName;

	// Sets default values for this actor's properties
	AGun();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void FireGun(AActor* actor) PURE_VIRTUAL(AGun::FireGun, ;);

	void RestoreAmmo(int ammo);

	void ReloadClip();

	UFUNCTION(BlueprintCallable, Category = Ammo)
		void ConsumeAmmo(int ammo);

	UFUNCTION(BlueprintCallable, Category = Ammo)
		int GetAmmoInClip();

	UFUNCTION(BlueprintCallable, Category = Ammo)
		int GetReserveAmmo();

	UFUNCTION(BlueprintCallable, Category = Ammo)
		bool ClipCanReload();

	void SetAmmoInClip(int ammo);
	void SetReserveAmmo(int ammo);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	int reserveAmmo, ammoInClip;
};
