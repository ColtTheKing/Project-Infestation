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
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Health)
		int maxHp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Health)
		int maxShieldHp;

	// Sets default values for this component's properties
	UHealthComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		int GetCurrentHp();

	UFUNCTION(BlueprintCallable)
		int GetCurrentShieldHp();

	void TakeDamage(int damage);
	void RestoreHp(int hp);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	int currentHp;
	int currentShieldHp;
};
