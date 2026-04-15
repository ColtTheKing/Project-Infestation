// Fill out your copyright notice in the Description page of Project Settings.

#include "InfestationUtilities.h"

bool UInfestationUtilities::GetNormalisedMousePositionInGeometry(UObject* WorldContextObject, FGeometry Geometry, FVector2D& Position)
{
	FVector2D pixelPosition;
	FVector2D viewportMinPosition;
	FVector2D viewportMaxPosition;

	// Get the top left and bottom right viewport positions
	USlateBlueprintLibrary::LocalToViewport(WorldContextObject, Geometry, FVector2D(0, 0), pixelPosition, viewportMinPosition);
	USlateBlueprintLibrary::LocalToViewport(WorldContextObject, Geometry, Geometry.GetLocalSize(), pixelPosition, viewportMaxPosition);

	// Get the mouse's current position in the viewport
	FVector2D mousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(WorldContextObject);

	// Determine where the mouse is relative to the widget geometry
	Position = (mousePosition - viewportMinPosition) / (viewportMaxPosition - viewportMinPosition);

	// Calculate if the mouse is inside the geometry or not
	return FMath::Min(Position.X, Position.Y) >= 0.f && FMath::Max(Position.X, Position.Y) <= 1.f;
}

TArray<AActor*> UInfestationUtilities::QuerySurroundingActorsFromActor(
	AActor* originActor, float radius, 
	const TArray<TEnumAsByte<EObjectTypeQuery>>& objectTypes, TArray<AActor*> actorsToIgnore, 
	EDrawDebugTrace::Type drawDebugTrace, FLinearColor traceColor, FLinearColor traceHitColor, float drawTime)
{
	if (originActor == nullptr)
		return TArray<AActor*>();

	FVector actorLocation = originActor->GetActorLocation();
	actorsToIgnore.Add(originActor);

	TArray<FHitResult> hitResults;
	bool bhit = UKismetSystemLibrary::SphereTraceMultiForObjects(
		originActor->GetWorld(), actorLocation, actorLocation, radius, objectTypes, false,
		actorsToIgnore, drawDebugTrace, hitResults, true,
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

TArray<AActor*> UInfestationUtilities::QuerySurroundingActorsFromComponent(
	USceneComponent* originComponent, float radius,
	const TArray<TEnumAsByte<EObjectTypeQuery>>& objectTypes, TArray<AActor*> actorsToIgnore,
	EDrawDebugTrace::Type drawDebugTrace, FLinearColor traceColor, FLinearColor traceHitColor, float drawTime)
{
	if (originComponent == nullptr)
		return TArray<AActor*>();

	FVector componentLocation = originComponent->GetComponentLocation();
	actorsToIgnore.Add(originComponent->GetOwner());

	TArray<FHitResult> hitResults;
	bool bhit = UKismetSystemLibrary::SphereTraceMultiForObjects(
		originComponent->GetWorld(), componentLocation, componentLocation, radius, objectTypes, false,
		actorsToIgnore, drawDebugTrace, hitResults, true,
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
