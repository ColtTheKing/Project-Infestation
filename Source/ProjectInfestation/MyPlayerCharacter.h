// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "Components/ChildActorComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include <ProjectInfestation/InteractableActor.h>
#include <ProjectInfestation/Gun.h>
#include <ProjectInfestation/HealthComponent.h>

#include "MyPlayerCharacter.generated.h"

UCLASS()
class PROJECTINFESTATION_API AMyPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyPlayerCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayerSpecs)
		float interactRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		UCameraComponent* playerCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
		USkeletalMeshComponent* playerArms;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gun)
		UChildActorComponent* heldGun;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health)
		UHealthComponent* health;

	UFUNCTION(BlueprintCallable, Category = Health)
		void TakeDamage(int damage);

	UFUNCTION(BlueprintCallable, Category = Health)
		void RestoreHp(int hp);

	UFUNCTION(BlueprintCallable, Category = Ammo)
		void RestoreAmmo(int ammo);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float axis);
	void MoveRight(float axis);
	void Interact();
	void FireWeapon();
	void ReloadWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	FHitResult ShootRay(float length);
};
