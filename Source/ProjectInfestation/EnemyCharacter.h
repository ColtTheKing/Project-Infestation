// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayTagAssetInterface.h"
#include "GameplayTagContainer.h"
#include "Components/CapsuleComponent.h"
#include "BehaviorTree/BehaviorTree.h"

#include "AI/PatrolPath.h"

#include "EnemyCharacter.generated.h"

class AEnemySpawner;

UCLASS()
class PROJECTINFESTATION_API AEnemyCharacter : public ACharacter, public IGameplayTagAssetInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// From IGameplayTagAssetInterface
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;

	// Getters for Enemy
	FORCEINLINE FGameplayTag GetEnemyType() { return enemyType; }

	// Getters for AI
	FORCEINLINE int GetAttackDamage() { return attackDamage; }
	FORCEINLINE float GetAttackRadius() { return attackRadius; }
	FORCEINLINE FGameplayTagContainer GetAttackTargets() { return attackTargets; }
	FORCEINLINE FGameplayTag GetEnemyState() { return currentState; }
	FORCEINLINE APatrolPath* GetPatrolPath() { return patrolPath; }
	FORCEINLINE bool IsBiDirectional() { return biDirectional; }

	// Setter for AI
	// NOTE: For CombatManager to change enemy state. Should replace as CombatManager should not be
	//       changing the enemy state directly, it should just tell the enemy what it can do.
	FORCEINLINE void SetEnemyState(FGameplayTag state) { currentState = state; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Type of the enemy
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GameplayTags", meta=(Categories="Enemy.Type"))
		FGameplayTag enemyType;

	// Behavior state of the enemy
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AI", meta=(DisplayName="Starting State", Categories="Enemy.State"))
		FGameplayTag currentState;

	// The patrol path the enemy follows
	UPROPERTY(EditAnywhere, Category = "AI")
		APatrolPath* patrolPath;

	// Patroling behavior of the enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		bool biDirectional = false;

	// Gameplay-related tags associated with attack targets
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
		FGameplayTagContainer attackTargets;

	// Attack radius of the enemy AI
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
		float attackRadius;

	// Attack damage of the enemy AI
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
		int attackDamage;
};