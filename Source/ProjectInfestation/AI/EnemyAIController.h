// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"

#include "AIObjectiveGenerationComponent.h"
#include "AIBehaviorSelectorComponent.h"
#include "Behaviors/AIBehavior.h"

#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTINFESTATION_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintReadOnly, Transient, meta = (AllowPrivateAccess))
		UBlackboardComponent* blackboardComp;

	UPROPERTY(BlueprintReadOnly, Transient, meta = (AllowPrivateAccess))
		UBehaviorTreeComponent* behaviorComp;

	/**
	 * Perception component that handles the senses of the controlled actor (sight, sound, etc.).
	 * Created in C++ to ensure that each child enemy controller will have one.
	 * 
	 * IMPORTANT: Only modify in the C++ if the component needs to be updated for each child.
	 */
	UPROPERTY(VisibleAnywhere, Transient)
		UAIPerceptionComponent* perceptionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient, meta = (AllowPrivateAccess))
		UAIObjectiveGenerationComponent* objectiveGenerationComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient, meta = (AllowPrivateAccess))
		UAIBehaviorSelectorComponent* behaviorSelectorComp;

public:
	/* Constructor */
	AEnemyAIController(const FObjectInitializer& objectInitializer);

	/**
	 * Runs logic for meleeing a target including animations, sounds, damage applied, etc.
	 * 
	 * NOTE: Meant to be inherited by the child AI controllers.
	 */
	virtual void MeleeAttack();

	/**
	 * Checks whether a actor is a valid attack target.
	 * @param actor: Actor to check.
	 * @return True if it's a valid attack target.
	 */
	UFUNCTION(BlueprintCallable)
		bool ValidAttackTarget(AActor* actor);

	/**
	 * Sets the attack target in both the controller and blackboard.
	 * @param attackTarget: The attack target to set to.
	 */
	UFUNCTION(BlueprintCallable)
		void SetAttackTarget(AActor* attackTarget = nullptr);

	/**
	 * Checks whether the actor was succussfully sensed (wrapper function).
	 * @param stimulus: The stimulus to check.
	 */
	UFUNCTION(BlueprintCallable)
		bool WasSuccussfullySensed(FAIStimulus const stimulus);

	
	// Runs a behavior with default variables.
	UFUNCTION(BlueprintCallable)
		void RunBehavior(UAIBehavior* behavior);

	// Runs a behavior with a corresponding objective option.
	UFUNCTION(BlueprintCallable)
		void RunBehaviorOption(const FAIBehaviorOption& behaviorOption);

	/**
	 * Alerts enemies around the controller's pawn using a local combat area.
	 * TODO: Shouldn't take a target actor, the combat manager should decide what the attack target is. 
	 *       This means there should be a separate event in the combat mangager for alerting enemies. Too
	 *       much work for little benefit at the moment.
	 * @param targetActor: Actor for those enemies to target.
	 */
	UFUNCTION(BlueprintCallable)
		void AlertLocalEnemies(AActor* targetActor);

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return blackboardComp; }
	FORCEINLINE UBehaviorTreeComponent* GetBehaviorComp() const { return behaviorComp; }

protected:
	virtual void OnPossess(class APawn* inPawn) override;
	virtual void OnUnPossess() override;

	/* Current target actor of the enemy. */
	UPROPERTY(BlueprintReadOnly)
		AActor* targetActor;
};
