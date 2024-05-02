// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayTagAssetInterface.h"
#include "GameplayTagContainer.h"
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
#include <ProjectInfestation/AI/AttackTargetInterface.h>
#include "Templates/SharedPointer.h"

#include "MyPlayerCharacter.generated.h"

UCLASS(meta=(PrioritizeCategories="GameplayTags AI"))
class PROJECTINFESTATION_API AMyPlayerCharacter : public ACharacter, public IGameplayTagAssetInterface, public IAttackTargetInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyPlayerCharacter();

	// Gameplay-related tags associated with this actor 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameplayTags")
		FGameplayTagContainer gameplayTags;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayerSpecs)
		float interactRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		UCameraComponent* playerCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
		USkeletalMeshComponent* playerArms;

	//Temporary holder component to position the gun in the arms
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gun)
		USceneComponent* armGunAttachment;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gun)
	//	TArray<AGun*> heldWeapons;

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

	UFUNCTION(BlueprintCallable, Category = Ammo)
		AWeapon* GetActiveWeapon();

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

	// From IGameplayTagAssetInterface
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;

	UFUNCTION(BlueprintCallable, Category = Shoot)
		FHitResult ShootRay(float length);

	virtual int GetMaxNumberOfAttackers() const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//void SetActiveWeapon(FArsenalWeapon weapon);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI", meta = (AllowPrivateAccess))
		int maxNumberOfAttackers;
};
