// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "BehaviorTree/BehaviorTree.h"

#include "HealthComponent.h"
#include "AI/PatrolPath.h"

#include "EnemyCharacter.generated.h"

class AEnemySpawner;

UCLASS()
class PROJECTINFESTATION_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health)
		UHealthComponent* health;*/

	// Sets default values for this character's properties
	AEnemyCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/*UFUNCTION(BlueprintCallable, Category = Damage)
		virtual void TakeDamage(int damage) PURE_VIRTUAL(AEnemyCharacter::TakeDamage, ;);*/

	FORCEINLINE int GetAttackDamage() { return attackDamage; }
	FORCEINLINE float GetAttackRadius() { return attackRadius; }

	// Used for behavior tree
	FORCEINLINE UBehaviorTree* GetBehaviorTree() { return enemyBehaviorTree; }
	FORCEINLINE APatrolPath* GetPatrolPath() { return patrolPath; }
	FORCEINLINE bool IsBiDirectional() { return biDirectional; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Determines the behaviors of the enemy
	UPROPERTY(EditAnywhere, Category = "AI")
		UBehaviorTree* enemyBehaviorTree;

	// The patrol path the enemy follows
	UPROPERTY(EditAnywhere, Category = "AI")
		APatrolPath* patrolPath;

	// Patroling behavior of the enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		bool biDirectional = false;

	// Attack radius of the enemy AI
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
		float attackRadius;

	// Attack damage of the enemy AI
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
		int attackDamage;
};