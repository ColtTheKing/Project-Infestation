// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Set up collision
	// TODO: Change so that collision is mapped to specific attack, not just the character's model

	//GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::OnOverlapBegin);
	//GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AEnemyCharacter::OnOverlapEnd);
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemyCharacter::TakeDamage(int damage)
{
	//Could pass in a damage type later so the actor can respond differently

	health->TakeDamage(damage);

	UE_LOG(LogTemp, Warning, TEXT("Enemy took %d damage, %d health remaining"), damage, health->GetCurrentHp());

	if (health->GetCurrentHp() <= 0)
	{
		Destroy();
	}
	else
	{
		//Do any code for when the character gets hit
	}
}