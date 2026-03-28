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
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "InteractableActor.h"
#include "Gun.h"
#include "MessageLogComponent.h"
#include "ArsenalComponent.h"
#include "InfestationGameMode.h"
#include "AI/AttackTargetInterface.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GameplayTags")
		FGameplayTagContainer gameplayTags;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayerSpecs)
		float interactRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		UCameraComponent* playerCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
		USkeletalMeshComponent* playerArms;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gun)
		UChildActorComponent* heldGrenade;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Messages)
		UMessageLogComponent* messageLog;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Arsenal)
		UArsenalComponent* weaponArsenal;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AI")
		UAIPerceptionStimuliSourceComponent* stimuliSourceComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
		bool playerUIOpen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess))
		int maxNumberOfAttackers;
		
	//Acceleration for the short initial portion of the thrust (should be higher than post startup)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thruster", meta = (AllowPrivateAccess))
		float startupAcceleration;

		//Acceleration for the rest of the thrust after startup (should be lower than startup)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thruster", meta = (AllowPrivateAccess))
		float postStartupAcceleration;

	//Affects how much the player is able to turn to either side while thrusting
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thruster", meta = (AllowPrivateAccess))
		float percentControlDuringThrust;

	//How long the player stays in "startup acceleration" and how long they have to wait before stopping the thrust
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thruster", meta = (AllowPrivateAccess))
		float startupDuration;

	//Max energy capacity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thruster", meta = (AllowPrivateAccess))
		float maxEnergy;

	//How much energy you regain per second
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thruster", meta = (AllowPrivateAccess))
		float energyRegenRate;

	//How much energy is consumed when pressing thrust initially
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thruster", meta = (AllowPrivateAccess))
		float thrustInitalEnergyCost;

	//How much energy is consumed per second when continuing to thrust after the startup
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thruster", meta = (AllowPrivateAccess))
		float thrustEnergyCostPerSecond;

	//The minimum amount of energy you need to have to be allowed to start a thrust
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thruster", meta = (AllowPrivateAccess))
		float minEnergyRequiredToThrust;

	//Current energy made visible for debugging
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Thruster")
		float currentEnergy;

	UFUNCTION(BlueprintCallable, Category = Ammo)
		void RestoreAmmo(FName ammoType, int ammo);

	UFUNCTION(BlueprintImplementableEvent, Category = Death)
		void KillPlayer();

	UFUNCTION(BlueprintCallable, Category = Ammo)
		AWeapon* GetActiveWeapon();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void ThrusterTick(float DeltaTime);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Jump() override;
	void MoveForward(float axis);
	void MoveRight(float axis);
	void ActivateThruster();
	void DeactivateThruster();
	void StartDecelerating();
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

	UFUNCTION(BlueprintImplementableEvent, Category = Arsenal)
		void OpenWeaponWheel();
	UFUNCTION(BlueprintImplementableEvent, Category = Arsenal)
		void CloseWeaponWheel();

	// From IGameplayTagAssetInterface
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;

	UFUNCTION(BlueprintCallable, Category = Shoot)
		FHitResult ShootRay(float length);

	virtual int GetMaxNumberOfAttackers() const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	bool shouldDeactivateThrusterLater; //true when player lets go of thrust key, to wait for initial thrust to finish
	bool currentlyThrusting;
	float timeSinceStartingThrust;
	FVector thrustDirection;
};
