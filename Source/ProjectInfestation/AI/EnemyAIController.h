// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
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
	
public:

	AEnemyAIController(const FObjectInitializer& objectInitializer);

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return blackboardComp; }
	FORCEINLINE UBehaviorTreeComponent* GetBehaviorComp() const { return behaviorComp; }

protected:

	virtual void OnPossess(class APawn* inPawn) override;
	virtual void OnUnPossess() override;

};
