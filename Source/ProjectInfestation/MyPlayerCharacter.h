// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include <ProjectInfestation/InteractableActor.h>

#include "MyPlayerCharacter.generated.h"

UCLASS()
class PROJECTINFESTATION_API AMyPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyPlayerCharacter();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = PlayerSpecs)
		float interactRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		UCameraComponent* playerCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
		USkeletalMeshComponent* playerArms;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float axis);
	void MoveRight(float axis);
	void Interact();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	FHitResult ShootRay(float length);
};
