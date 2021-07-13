// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Components/StaticMeshComponent.h"

#include "Gun.generated.h"

UCLASS()
class PROJECTINFESTATION_API AGun : public AWeapon
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gun)
		UStaticMeshComponent* shotPosition;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gun)
		int spreadAngle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gun)
		int pelletsPerShot;										

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gun)
		int ammoConsumedPerShot;

	// Sets default values for this actor's properties
	AGun();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ReloadClip();

	void ConsumeAmmo(int ammo) override;

	UFUNCTION(BlueprintCallable, Category = Ammo)
		bool ClipCanReload();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	
};
