// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Components/CapsuleComponent.h"
#include <ProjectInfestation/HealthComponent.h>

#include "EnemyCharacter.generated.h"

UCLASS()
class PROJECTINFESTATION_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

	//Can be used for having enemies interact with stuff in future, but are currently unnecessary
	/*UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);*/

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health)
		UHealthComponent* health;

	// Sets default values for this character's properties
	AEnemyCharacter();

	UFUNCTION(BlueprintCallable, Category = Damage)
		virtual void TakeDamage(float damage);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};