// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "Templates/SharedPointer.h"
#include "BasicEnemy.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTINFESTATION_API ABasicEnemy : public AEnemyCharacter
{
	GENERATED_BODY()
	
public:	
	ABasicEnemy();

	void TakeDamage(int damage) override;

	void SetEnemySpawner(TWeakObjectPtr<AEnemySpawner> aEnemySpawner);

	// Called every frame
	void Tick(float DeltaTime) override;

protected:
	// Called on level load
	void BeginPlay() override;

private:
	TWeakObjectPtr<AEnemySpawner> enemySpawner;

};
