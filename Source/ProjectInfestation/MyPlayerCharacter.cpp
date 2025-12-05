// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerCharacter.h"

// Sets default values
AMyPlayerCharacter::AMyPlayerCharacter() : Super()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->AirControl = 0.2f;

	playerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	playerCamera->SetupAttachment(GetRootComponent());
	playerCamera->bUsePawnControlRotation = true;

	playerArms = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PlayerArms"));
	playerArms->SetupAttachment(playerCamera);

	messageLog = CreateDefaultSubobject<UMessageLogComponent>(TEXT("MessageLog"));
	weaponArsenal = CreateDefaultSubobject<UArsenalComponent>(TEXT("WeaponArsenal"));

	// Designate as Stimulus Source
	stimuliSourceComponent = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("AIStimuliSource"));
}

// Called when the game starts or when spawned
void AMyPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	weaponArsenal->SetupWeapons(playerArms);
	currentEnergy = maxEnergy;
}

// Called every frame
void AMyPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Regenerate energy if missing any
	if (currentEnergy < maxEnergy)
	{
		currentEnergy += energyRegenRate * DeltaTime;

		if (currentEnergy > maxEnergy)
			currentEnergy = maxEnergy;
	}

	// Deal with thrust movement if currently thrusting
	if (currentlyThrusting)
	{
		AddMovementInput(thrustDirection, 1);
		timeSinceStartingThrust += DeltaTime;

		//If the player let go of thrust and enough time is elapsed we can slow down
		if (shouldDeactivateThruster && timeSinceStartingThrust >= startupDuration)
			StartDecelerating();
	}

	// If the weapon attack button is being held down, try to do it every frame
	if (GetActiveWeapon())
	{
		AGun* myGun = Cast<AGun>(GetActiveWeapon());
		if (myGun && myGun->constantlyShooting)
			myGun->UseWeapon(this);
	}
}

AWeapon* AMyPlayerCharacter::GetActiveWeapon()
{
	return weaponArsenal->GetActiveWeapon();
}

// Called to bind functionality to input
void AMyPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Thrust", IE_Pressed, this, &AMyPlayerCharacter::ActivateThruster);
	PlayerInputComponent->BindAction("Thrust", IE_Released, this, &AMyPlayerCharacter::DeactivateThruster);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AMyPlayerCharacter::StartCrouching);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AMyPlayerCharacter::StopCrouching);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMyPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyPlayerCharacter::MoveRight);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMyPlayerCharacter::Interact);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMyPlayerCharacter::FireWeapon);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AMyPlayerCharacter::StopFiringWeapon);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AMyPlayerCharacter::ReloadWeapon);

	PlayerInputComponent->BindAction("PreviousWeapon", IE_Pressed, this, &AMyPlayerCharacter::PreviousWeapon);
	PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, this, &AMyPlayerCharacter::NextWeapon);

	PlayerInputComponent->BindAction("SwitchWeapon1", IE_Pressed, this, &AMyPlayerCharacter::SwitchWeapon1);
	PlayerInputComponent->BindAction("SwitchWeapon2", IE_Pressed, this, &AMyPlayerCharacter::SwitchWeapon2);
	PlayerInputComponent->BindAction("SwitchWeapon3", IE_Pressed, this, &AMyPlayerCharacter::SwitchWeapon3);
	PlayerInputComponent->BindAction("SwitchWeapon4", IE_Pressed, this, &AMyPlayerCharacter::SwitchWeapon4);
	PlayerInputComponent->BindAction("SwitchGrenade", IE_Pressed, this, &AMyPlayerCharacter::SwitchGrenade);

	PlayerInputComponent->BindAction("WeaponWheel", IE_Pressed, this, &AMyPlayerCharacter::OpenWeaponWheel);
	PlayerInputComponent->BindAction("WeaponWheel", IE_Released, this, &AMyPlayerCharacter::CloseWeaponWheel);

	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &AMyPlayerCharacter::PauseGame).bExecuteWhenPaused = true;
}

void AMyPlayerCharacter::MoveForward(float axis)
{
	if (currentlyThrusting)
		return;
	
	const FRotator rotation = Controller->GetControlRotation();
	const FRotator yawRotation(0, rotation.Yaw, 0);

	const FVector direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(direction, axis);
}

void AMyPlayerCharacter::MoveRight(float axis)
{
	if (currentlyThrusting)
		return;

	const FRotator rotation = Controller->GetControlRotation();
	const FRotator yawRotation(0, rotation.Yaw, 0);

	const FVector direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(direction, axis);
}

void AMyPlayerCharacter::ActivateThruster()
{
	if (currentEnergy < thrustEnergyCost || currentEnergy < minEnergyRequiredToThrust)
		return; //give player some indication that they can't activate due to low energy

	currentEnergy -= thrustEnergyCost;

	FVector direction = GetLastMovementInputVector();
	direction.Normalize();

	currentlyThrusting = true;
	thrustDirection = direction;
	timeSinceStartingThrust = 0;
	shouldDeactivateThruster = false;
	GetCharacterMovement()->MaxWalkSpeed = 3000.0f;
	GetCharacterMovement()->MaxAcceleration = 10000.0f;

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Direction = %f, %f"), direction.X, direction.Y));
}

void AMyPlayerCharacter::DeactivateThruster()
{
	//Delay deceleration if the startup period has not ended yet
	if (timeSinceStartingThrust < startupDuration)
	{
		shouldDeactivateThruster = true;
		return;
	}

	//actually start decelerating if it has been enough time since starting
	StartDecelerating();
}

void AMyPlayerCharacter::StartDecelerating()
{
	shouldDeactivateThruster = false;
	currentlyThrusting = false;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	GetCharacterMovement()->MaxAcceleration = 2048.0f;
}

void AMyPlayerCharacter::StartCrouching()
{
	if (!bIsCrouched)
		Crouch();
}

void AMyPlayerCharacter::StopCrouching()
{
	if (bIsCrouched)
		UnCrouch();
}

void AMyPlayerCharacter::Interact()
{
	if (playerUIOpen)
		return;

	FHitResult rayHit = ShootRay(interactRange);
	AInteractableActor* hitActor = Cast<AInteractableActor>(rayHit.GetActor());

	if (hitActor)
	{
		hitActor->Interact();
	}
}

void AMyPlayerCharacter::FireWeapon()
{
	if (playerUIOpen)
		return;

	AWeapon* myWeapon = weaponArsenal->GetActiveWeapon();

	if (myWeapon)
		myWeapon->UseWeapon(this);
}

void AMyPlayerCharacter::StopFiringWeapon()
{
	AWeapon* myWeapon = weaponArsenal->GetActiveWeapon();

	if (myWeapon)
		myWeapon->StopUsingWeapon();
}

void AMyPlayerCharacter::ReloadWeapon()
{
	if (playerUIOpen)
		return;

	AWeapon* myWeapon = weaponArsenal->GetActiveWeapon();

	if (myWeapon)
	{
		AGun* myGun = Cast<AGun>(myWeapon);

		if (myGun)
			myGun->ReloadClip();
	}
}

void AMyPlayerCharacter::PreviousWeapon()
{
	weaponArsenal->ActivatePrevious();
}

void AMyPlayerCharacter::NextWeapon()
{
	weaponArsenal->ActivateNext();
}

void AMyPlayerCharacter::SwitchWeapon1()
{
	weaponArsenal->ActivateIndex(0);
}

void AMyPlayerCharacter::SwitchWeapon2()
{
	weaponArsenal->ActivateIndex(1);
}

void AMyPlayerCharacter::SwitchWeapon3()
{
	weaponArsenal->ActivateIndex(2);
}

void AMyPlayerCharacter::SwitchWeapon4()
{
	weaponArsenal->ActivateIndex(3);
}

void AMyPlayerCharacter::SwitchGrenade()
{
	weaponArsenal->ActivateAndEnableGrenade();
}

void AMyPlayerCharacter::PauseGame()
{
	AInfestationGameMode* infestationGameMode = Cast<AInfestationGameMode>(GetWorld()->GetAuthGameMode());
	if (infestationGameMode && !infestationGameMode->IsPaused())
	{
		// Valid and game isn't already paused
		infestationGameMode->PauseGame();
	}
	else if (infestationGameMode)
	{
		// Valid and the game isn't paused
		infestationGameMode->UnpauseGame();
	}
}

void AMyPlayerCharacter::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	TagContainer.AppendTags(gameplayTags);
}

FHitResult AMyPlayerCharacter::ShootRay(float length)
{
	FVector rayLocation;
	FRotator rayRotation;
	FVector endRay = FVector::ZeroVector;

	APlayerController* const playerController = GetWorld()->GetFirstPlayerController();
	if (playerController)
	{
		playerController->GetPlayerViewPoint(rayLocation, rayRotation);

		endRay = rayLocation + (rayRotation.Vector() * length);
	}

	//Params are a tag for debugging, whether to use complex collision, and which object to ignore
	FCollisionQueryParams rayParams(SCENE_QUERY_STAT(ShootRay), true, this);
	FHitResult hit(ForceInit);
	GetWorld()->LineTraceSingleByChannel(hit, rayLocation, endRay, ECC_Visibility, rayParams);

	return hit;
}

int AMyPlayerCharacter::GetMaxNumberOfAttackers() const
{
	return maxNumberOfAttackers;
}

void AMyPlayerCharacter::RestoreAmmo(FName ammoType, int ammo)
{
	weaponArsenal->AddAmmo(ammoType, ammo);
}