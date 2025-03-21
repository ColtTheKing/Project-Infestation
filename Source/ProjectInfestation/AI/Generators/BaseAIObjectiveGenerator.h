// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Perception/AIPerceptionComponent.h"
#include "GameplayTagAssetInterface.h"

#include "../Objectives/AIObjective.h"

#include "BaseAIObjectiveGenerator.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class PROJECTINFESTATION_API UBaseAIObjectiveGenerator : public UObject, public IGameplayTagAssetInterface
{
	GENERATED_BODY()
	
public:
	// Set default values
	UBaseAIObjectiveGenerator();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void OnUpdate();
	
	UFUNCTION(BlueprintCallable)
		UAIObjective* GetOrCreateObjective(TSubclassOf<UAIObjective> objectiveType);

	UFUNCTION(BlueprintCallable)
		UAIObjective* GetExistingObjective(TSubclassOf<UAIObjective> objectiveType);

	// Wrapper for UKismetSystemLibrary::SphereTraceMultiForObjects, makes it simpler for child blueprints to call and parse found actors.
	// NOTE: If performance/memory is an issue down the road, sphere trace can be swapped for a box trace. Sphere trace is very unlikely to be the issue though. 
	UFUNCTION(BlueprintCallable, meta=(AutoCreateRefTerm="actorsToIgnore"))
		TArray<AActor*> QuerySurroundingActors(float radius, 
			const TArray<TEnumAsByte<EObjectTypeQuery>> &objectTypes, TArray<AActor*> actorsToIgnore,
			FLinearColor traceColor = FLinearColor::Red, FLinearColor traceHitColor = FLinearColor::Green, float drawTime = 5.0f);

	UFUNCTION(BlueprintCallable)
		TArray<UAIObjective*> GetExistingObjectives();

	// From IGameplayTagAssetInterface
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;

	FORCEINLINE void SetOwnerPerceptionComponent(
		TWeakObjectPtr<UAIPerceptionComponent> perceptionComponent) { ownerPerceptionComponent = perceptionComponent; };

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI Objective Generator")
		FGameplayTag objectiveGeneratorType;

	// Usually set by the ObjectiveGenerationComponent but can be set on it's own.
	UPROPERTY(BlueprintReadWrite, Category="AI Objective Generator")
		TWeakObjectPtr<UAIPerceptionComponent> ownerPerceptionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI Objective Generator")
		TArray<TObjectPtr<UAIObjective>> existingObjectives;
};
