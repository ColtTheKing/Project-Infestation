// Fill out your copyright notice in the Description page of Project Settings.

#include "SwarmerAIController.h"

#include "../MyPlayerCharacter.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

ASwarmerAIController::ASwarmerAIController(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	/*if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("TEST"));*/
}

void ASwarmerAIController::HandleSightSense(AActor* actor, FAIStimulus const stimulus)
{
	// Only want to continue if the Actor sighted is the player.
	AMyPlayerCharacter* player = Cast<AMyPlayerCharacter>(actor);
	if (player == NULL)
		return;

	if (stimulus.WasSuccessfullySensed())
		// Player found.
		GetBlackboardComp()->SetValueAsObject("TargetActor", player);
	else
		// Player lost.
		GetBlackboardComp()->SetValueAsObject("TargetActor", NULL);
}
