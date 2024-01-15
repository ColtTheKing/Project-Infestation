// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTINFESTATION_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

private:
	UPROPERTY(Transient)
		UBlackboardComponent* blackboardComp;

	UPROPERTY(Transient)
		UBehaviorTreeComponent* behaviorComp;

	/*
	* Perception component that handles the senses of the controlled actor (sight, sound, etc.).
	* Created in C++ to ensure that each child enemy controller will have one.
	* 
	* IMPORTANT: Only modify in the C++ if the component needs to be updated for each child.
	*/
	UPROPERTY(VisibleAnywhere, Transient)
		UAIPerceptionComponent* perceptionComp;
		
	
public:
	AEnemyAIController(const FObjectInitializer& objectInitializer);

	/*
	* Runs logic for meleeing a target including animations, sounds, damage applied, etc.
	* 
	* NOTE: Meant to be inherited by the child AI controllers.
	*/
	virtual void MeleeAttack();

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return blackboardComp; }
	FORCEINLINE UBehaviorTreeComponent* GetBehaviorComp() const { return behaviorComp; }

protected:
	virtual void OnPossess(class APawn* inPawn) override;
	virtual void OnUnPossess() override;
};
