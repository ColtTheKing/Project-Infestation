// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Generators/BaseAIObjectiveGenerator.h"
#include "Objectives/AIObjective.h"

#include "AIObjectiveGenerationComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTINFESTATION_API UAIObjectiveGenerationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAIObjectiveGenerationComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category="AI Objective Generation")
		TArray<TObjectPtr<UBaseAIObjectiveGenerator>> objectiveGenerators;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
		float generatorsUpdateTimer;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		void UpdateGenerators();

	UFUNCTION(BlueprintCallable)
		TArray<UAIObjective*> GetGeneratedObjectives();

	// Development function for testing a single generator.
	// TODO: If function ends up actually used for the game, change objectiveGenerators to hash table for fast search.
	UFUNCTION(BlueprintCallable)
		UBaseAIObjectiveGenerator* GetGenerator(TSubclassOf<UBaseAIObjectiveGenerator> objectiveGeneratorClass);
};
