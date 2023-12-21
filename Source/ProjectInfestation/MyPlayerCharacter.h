// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "Components/ChildActorComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include <ProjectInfestation/InteractableActor.h>
#include <ProjectInfestation/Gun.h>
#include <ProjectInfestation/HealthComponent.h>
#include <ProjectInfestation/MessageLogComponent.h>
#include <ProjectInfestation/ArsenalComponent.h>
#include <ProjectInfestation/InfestationGameMode.h>
#include "Templates/SharedPointer.h"

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
		TArray<UChildActorComponent*> heldWeapons;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gun)
		UChildActorComponent* heldGrenade;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Messages)
		UMessageLogComponent* messageLog;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Arsenal)
		UArsenalComponent* weaponArsenal;

	UFUNCTION(BlueprintCallable, Category = Ammo)
		void RestoreAmmo(FName ammoType, int ammo);

	UFUNCTION(BlueprintImplementableEvent, Category = Death)
		void KillPlayer();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float axis);
	void MoveRight(float axis);
	void StartCrouching();
	void StopCrouching();
	void Interact();
	void FireWeapon();
	void StopFiringWeapon();
	void ReloadWeapon();
	void PreviousWeapon();
	void SwitchWeapon1();
	void SwitchWeapon2();
	void SwitchWeapon3();
	void SwitchWeapon4();
	void SwitchGrenade();
	void NextWeapon();
	void PauseGame();

	UFUNCTION(BlueprintCallable, Category = Shoot)
		FHitResult ShootRay(float length);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//void SetActiveWeapon(FArsenalWeapon weapon);

private:
	//bool setGunYet;

	void SaveWeaponInfo();
};
