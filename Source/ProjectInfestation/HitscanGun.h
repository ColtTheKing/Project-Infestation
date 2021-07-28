// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gun.h"
#include <ProjectInfestation/EnemyCharacter.h>
#include <ProjectInfestation/HealthComponent.h>

#include "HitscanGun.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTINFESTATION_API AHitscanGun : public AGun
{
	GENERATED_BODY()
	
public:
	AHitscanGun();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, Category = Shoot)
		void UseWeapon(AActor* actor) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = Shoot)
		FHitResult ShootRay(AActor* actor, float length, float angleFromCenter = 0, float angleAround = 0);
};
