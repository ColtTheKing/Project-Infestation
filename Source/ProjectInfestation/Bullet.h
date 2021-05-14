// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include <ProjectInfestation/EnemyCharacter.h>
#include <ProjectInfestation/HealthComponent.h>

#include "Bullet.generated.h"

UCLASS()
class PROJECTINFESTATION_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Bullet)
		int damage;

	// Sets default values for this actor's properties
	ABullet();

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
