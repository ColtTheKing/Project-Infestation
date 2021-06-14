// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <vector>

#include "MessageLogComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTINFESTATION_API UMessageLogComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Messages)
		float messageDuration;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Messages)
		int maxMessages;

	// Sets default values for this component's properties
	UMessageLogComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = Messages)
		void AddMessage(FText message);

	UFUNCTION(BlueprintCallable, Category = Messages)
		FText GetMessageAt(int index);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	std::vector<FText> messages;
	std::vector<float> messageTimers;
};
