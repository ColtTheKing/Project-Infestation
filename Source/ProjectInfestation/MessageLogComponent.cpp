// Fill out your copyright notice in the Description page of Project Settings.


#include "MessageLogComponent.h"

// Sets default values for this component's properties
UMessageLogComponent::UMessageLogComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UMessageLogComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UMessageLogComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	int expiredMessages = 0;
	// Ticks down the timer of each of the messages
	for (size_t i = 0; i < messageTimers.size(); i++)
	{
		messageTimers[i] -= DeltaTime;

		if (messageTimers[i] <= 0)
			expiredMessages++;
	}

	// Removes messages that have been in the message log long enough
	for (size_t i = 0; i < expiredMessages; i++)
	{
		messages.erase(messages.begin());
		messageTimers.erase(messageTimers.begin());
	}
}

void UMessageLogComponent::AddMessage(FText message)
{
	// If the log is already full just bump the oldest one out
	if (messages.size() == maxMessages)
	{
		if (maxMessages == 0)
		{
			UE_LOG(LogTemp, Error, TEXT("MessageLogComponent::AddMessage(): Message log has zero capacity"));
			return;
		}

		messages.erase(std::prev(messages.end()));
		messageTimers.erase(std::prev(messageTimers.end()));
	}

	// Add a new message that will exist in the log for the message duration
	messages.insert(messages.begin(), message);
	messageTimers.insert(messageTimers.begin(), messageDuration);
}

FText UMessageLogComponent::GetMessageAt(int index)
{
	if (index >= 0 && index < messages.size())
		return messages[index];

	return FText();
}
