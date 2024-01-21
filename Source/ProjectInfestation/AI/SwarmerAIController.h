// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAIController.h"
#include "../EnemyCharacter.h"
#include "Perception/AIPerceptionTypes.h"
#include "SwarmerAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTINFESTATION_API ASwarmerAIController : public AEnemyAIController
{
	GENERATED_BODY()

public:
	ASwarmerAIController(const FObjectInitializer& objectInitializer);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*
	* Updates the target actor currently being sensed.
	* 
	* NOTE: Currently target actor will only update if the player is sensed.
	*/
	UFUNCTION(BlueprintCallable)
		void UpdateTargetActor(AActor* Actor, FAIStimulus const Stimulus);

	UFUNCTION(BlueprintCallable)
		virtual void MeleeAttack() override;
};
