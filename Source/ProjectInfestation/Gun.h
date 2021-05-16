// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class PROJECTINFESTATION_API AGun : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gun)
		int spreadAngle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gun)
		int bulletsPerShot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gun)
		float fireRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gun)
		int clipSize;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gun)
		int damagePerPellet;

	// Sets default values for this actor's properties
	AGun();

	virtual void FireGun(FVector bulletStart, FRotator gunRotation) PURE_VIRTUAL(AGun::FireGun, ;);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
