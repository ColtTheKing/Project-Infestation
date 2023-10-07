// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"

#include "HealthComponent.h"

#include "EnemyCharacter.generated.h"

class AEnemySpawner;

UCLASS()
class PROJECTINFESTATION_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health)
		UHealthComponent* health;

	// Sets default values for this character's properties
	AEnemyCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/*UFUNCTION(BlueprintCallable, Category = Damage)
		virtual void TakeDamage(int damage) PURE_VIRTUAL(AEnemyCharacter::TakeDamage, ;);*/

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	
};