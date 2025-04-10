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