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

	void FireGun(FVector bulletStart, FRotator gunRotation) override;

private:
	FHitResult ShootRay(FVector rayLocation, FRotator rayRotation);
};
