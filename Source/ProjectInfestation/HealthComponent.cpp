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
	currentHp = maxHp;
	currentShieldHp = maxShieldHp;
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::TakeDamage(int damage)
{
	int newShieldHp = currentShieldHp - damage;

	UE_LOG(LogTemp, Warning, TEXT("Character took damage of %d"), damage);

	//if shield broke or wasn't there
	if (newShieldHp <= 0)
	{
		currentHp -= damage - currentShieldHp;
		currentShieldHp = 0;
	}
	else
	{
		currentShieldHp = newShieldHp;
	}
}

void UHealthComponent::RestoreHp(int hp)
{
	if (maxHp < (hp + currentHp))
		currentHp = maxHp;
	else
		currentHp += hp;
}

int UHealthComponent::GetCurrentHp()
{
	return currentHp;
}

int UHealthComponent::GetCurrentShieldHp()
{
	return currentShieldHp;
}