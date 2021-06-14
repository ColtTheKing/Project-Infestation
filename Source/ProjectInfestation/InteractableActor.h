// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "InteractableActor.generated.h"

UCLASS()
class PROJECTINFESTATION_API AInteractableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Tooltips)
		FName actorName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Tooltips)
		FName interactActionWord;

	// Sets default values for this actor's properties
	AInteractableActor();

	UFUNCTION(BlueprintImplementableEvent, Category = Interactable)
		void Interact();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
