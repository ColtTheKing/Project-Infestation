// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAIObjectiveGenerator.h"

UBaseAIObjectiveGenerator::UBaseAIObjectiveGenerator()
{

}

UAIObjective* UBaseAIObjectiveGenerator::GetOrCreateObjective(TSubclassOf<UAIObjective> objectiveType)
{
	if (objectiveType == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s: ObjectiveType is invalid type."), *this->GetFName().ToString());
		return nullptr;
	}

	// Get existing
	for (auto& objective : existingObjectives)
	{
		if (objective->IsA(objectiveType))
			return objective;
	}
	
	// Create if it doesn't exist
	auto* newObjective = NewObject<UAIObjective>(this, objectiveType);
	existingObjectives.Add(newObjective);
	return newObjective;
}

TArray<AActor*> UBaseAIObjectiveGenerator::QuerySurroundingActors(float radius,
	const TArray<TEnumAsByte<EObjectTypeQuery>>& objectTypes, TArray<AActor*> actorsToIgnore,
	FLinearColor traceColor, FLinearColor traceHitColor, float drawTime)
{
	FVector actorLocation = ownerPerceptionComponent->GetOwner()->GetActorLocation(); 
	TWeakObjectPtr<AController> ownerController = Cast<AController>(ownerPerceptionComponent->GetOwner()); // Add owner actor to actors to ignore
	if (ownerController == nullptr) // NOTE: Would perfer this to be one line, however for now it's fine. Would need to change design to allow for it and I currently don't know how to do that
		// Owner is actor
		actorsToIgnore.Add(ownerPerceptionComponent->GetOwner());
	else
		// Owner is a controller
		actorsToIgnore.Add(ownerController->GetPawn());

	TArray<FHitResult> hitResults;
	bool bhit = UKismetSystemLibrary::SphereTraceMultiForObjects(
		GetWorld(), actorLocation, actorLocation, radius, objectTypes, false, 
		actorsToIgnore, EDrawDebugTrace::ForDuration, hitResults, true,
		traceColor, traceHitColor, drawTime);
	
	TArray<AActor*> queriedActors;
	if (!bhit) // None of the objectTypes hit
		return queriedActors;
	
	for (const auto& hitResult : hitResults)
	{
		queriedActors.Add(hitResult.GetActor());
	}
	return queriedActors;
}

TArray<UAIObjective*> UBaseAIObjectiveGenerator::GetExistingObjectives()
{
	return existingObjectives;
}

void UBaseAIObjectiveGenerator::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	TagContainer.AddTag(objectiveGeneratorType);
}

UWorld* UBaseAIObjectiveGenerator::GetWorld() const
{
	if (GetOuter() == nullptr)
		return nullptr;

	// Special case for UObject in the editor
	if (Cast<UPackage>(GetOuter()) != nullptr)
	{
		// GetOuter should return a UPackage and its Outer is a UWorld
		return Cast<UWorld>(GetOuter()->GetOuter());
	}

	// In all other cases...
	return GetOuter()->GetWorld();
}
