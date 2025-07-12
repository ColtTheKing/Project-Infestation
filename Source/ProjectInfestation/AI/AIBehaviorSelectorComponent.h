// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Behaviors/AIBehavior.h"
#include "Objectives/AIObjective.h"

#include "AIBehaviorSelectorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTINFESTATION_API UAIBehaviorSelectorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAIBehaviorSelectorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		UAIBehavior* SelectBehavior(const TArray<UAIObjective*>& availableObjectives);

	FORCEINLINE UAIBehavior* GetDefaultBehavior() { return defaultBehavior; }

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced, meta=(AllowPrivateAccess=true))
		TObjectPtr<UAIBehavior> defaultBehavior;

	UPROPERTY(BlueprintReadWrite, Instanced, meta=(AllowPrivateAccess=true))
		TObjectPtr<UAIBehavior> currentBehavior;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced, meta = (AllowPrivateAccess = true))
		TArray<TObjectPtr<UAIBehavior>> hightPriorityBehaviors;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced, meta=(AllowPrivateAccess=true))
		TArray<TObjectPtr<UAIBehavior>> behaviors;
};
