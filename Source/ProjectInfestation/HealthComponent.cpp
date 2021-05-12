// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::TakeDamage(int damage)
{
	int newShieldHp = shieldHp - damage;

	UE_LOG(LogTemp, Warning, TEXT("Player took damage of %d"), damage);

	//if shield broke or wasn't there
	if (newShieldHp <= 0)
	{
		currentHp -= damage - shieldHp;
		shieldHp = 0;

		if (currentHp < 0)
			currentHp = 0;
	}
	else
	{
		shieldHp = newShieldHp;
	}
}