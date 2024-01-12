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

	UFUNCTION(BlueprintCallable)
		void HandleSightSense(AActor* Actor, FAIStimulus const Stimulus);

	UFUNCTION(BlueprintCallable)
		void MeleeAttack() override;
};
