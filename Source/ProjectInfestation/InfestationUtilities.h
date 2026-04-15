// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Layout/Geometry.h" 
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

#include "InfestationUtilities.generated.h"

UCLASS()
class PROJECTINFESTATION_API UInfestationUtilities : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = UI)
		static bool GetNormalisedMousePositionInGeometry(UObject* WorldContextObject, FGeometry Geometry, FVector2D& Position);

	UFUNCTION(BlueprintCallable, Category = AI, meta=(AutoCreateRefTerm = "actorsToIgnore"))
		static TArray<AActor*> QuerySurroundingActorsFromActor(
			AActor* originActor, float radius, 
			const TArray<TEnumAsByte<EObjectTypeQuery>>& objectTypes, TArray<AActor*> actorsToIgnore,
			EDrawDebugTrace::Type drawDebugTrace = EDrawDebugTrace::None, FLinearColor traceColor = FLinearColor::Red,
			FLinearColor traceHitColor = FLinearColor::Green, float drawTime = 5.0f);

	UFUNCTION(BlueprintCallable, Category = AI, meta = (AutoCreateRefTerm = "actorsToIgnore"))
		static TArray<AActor*> QuerySurroundingActorsFromComponent(
			USceneComponent* originComponent, float radius,
			const TArray<TEnumAsByte<EObjectTypeQuery>>& objectTypes, TArray<AActor*> actorsToIgnore,
			EDrawDebugTrace::Type drawDebugTrace = EDrawDebugTrace::None, FLinearColor traceColor = FLinearColor::Red,
			FLinearColor traceHitColor = FLinearColor::Green, float drawTime = 5.0f);

};
