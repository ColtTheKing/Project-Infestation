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

	UFUNCTION(BlueprintImplementableEvent, Category = Shoot)
		void FireGun(AActor* actor) override;

protected:
	UFUNCTION(BlueprintCallable, Category = Shoot)
		FHitResult ShootRay(AActor* actor, float length, float angleFromCenter = 0, float angleAround = 0);

	//put in function(s) to calculate angles and make them blueprint callable
};
