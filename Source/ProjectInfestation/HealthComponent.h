// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTINFESTATION_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Health)
		int currentHp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Health)
		int shieldHp;

	UFUNCTION(BlueprintCallable, Category = "TakeDamage")
		void TakeDamage(int damage);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
