// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerCharacter.h"

// Sets default values
AMyPlayerCharacter::AMyPlayerCharacter()
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


	//setupGunsYet = false;
}

// Called when the game starts or when spawned
void AMyPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	////Set up child objects for all of the base guns
	//for (int i = 0; i < gunTypes.Num(); i++)
	//{
	//	AGun* heldWeapon = NewObject<AGun>(playerArms);
	//	//UChildActorComponent* heldWeapon = CreateDefaultSubobject<UChildActorComponent>(TEXT("HeldWeapon" + i));
	//	//heldWeapon->SetupAttachment(playerArms);
	//	heldWeapons.Add(heldWeapon);
	//}

	//AWeapon* heldGrenade = NewObject<AWeapon>(playerArms);
	///*heldGrenade = CreateDefaultSubobject<UChildActorComponent>(TEXT("HeldGrenade"));
	//heldGrenade->SetupAttachment(playerArms);*/

	//weaponArsenal->SetupWeapons(heldWeapons, heldGrenade, gunTypes);
}

// Called every frame
void AMyPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*if (!setupGunsYet)
	{
		weaponArsenal->SetupWeapons(heldWeapons, heldGrenade);
		setupGunsYet = true;
	}*/

	// If the weapon attack button is being held down, try to do it every frame

	/*if (heldWeapon)
	{
		AActor* gunActor = heldWeapon->GetChildActor();
		AGun* myGun = Cast<AGun>(gunActor);

		if (myGun && myGun->constantlyShooting)
		{
			myGun->UseWeapon(this);
		}
	}*/
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

	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &AMyPlayerCharacter::PauseGame).bExecuteWhenPaused = true;
}

void AMyPlayerCharacter::MoveForward(float axis)
{
	const FRotator rotation = Controller->GetControlRotation();
	const FRotator yawRotation(0, rotation.Yaw, 0);

	const FVector direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(direction, axis);
}

void AMyPlayerCharacter::MoveRight(float axis)
{
	const FRotator rotation = Controller->GetControlRotation();
	const FRotator yawRotation(0, rotation.Yaw, 0);

	const FVector direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(direction, axis);
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
	FHitResult rayHit = ShootRay(interactRange);
	AInteractableActor* hitActor = Cast<AInteractableActor>(rayHit.GetActor());

	if (hitActor)
	{
		hitActor->Interact();
	}
}

void AMyPlayerCharacter::FireWeapon()
{
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
	/*if (!setGunYet)
		return;

	SaveWeaponInfo();*/

	weaponArsenal->ActivatePrevious();
}

void AMyPlayerCharacter::NextWeapon()
{
	/*if (!setGunYet)
		return;

	SaveWeaponInfo();*/

	weaponArsenal->ActivateNext();
}

void AMyPlayerCharacter::SwitchWeapon1()
{
	/*if (!setGunYet)
		return;

	SaveWeaponInfo();*/

	weaponArsenal->ActivateIndex(0);
}

void AMyPlayerCharacter::SwitchWeapon2()
{
	/*if (!setGunYet)
		return;

	SaveWeaponInfo();*/

	weaponArsenal->ActivateIndex(1);
}

void AMyPlayerCharacter::SwitchWeapon3()
{
	/*if (!setGunYet)
		return;

	SaveWeaponInfo();*/

	weaponArsenal->ActivateIndex(2);
}

void AMyPlayerCharacter::SwitchWeapon4()
{
	/*if (!setGunYet)
		return;

	SaveWeaponInfo();*/

	weaponArsenal->ActivateIndex(3);
}

//void AMyPlayerCharacter::SaveWeaponInfo()
//{
//	if (heldWeapon)
//	{
//		AActor* weaponActor = heldWeapon->GetChildActor();
//		AWeapon* myWeapon = Cast<AGun>(weaponActor);
//
//		if (myWeapon)
//		{
//			weaponArsenal->SetActiveWeaponInfo(myWeapon->GetReserveAmmo(), myWeapon->GetAmmoInClip());
//		}
//	}
//}

void AMyPlayerCharacter::SwitchGrenade()
{
	/*if (!setGunYet)
		return;

	SaveWeaponInfo();*/
	
	weaponArsenal->ActivateGrenade();
}

//void AMyPlayerCharacter::SetActiveWeapon(FArsenalWeapon weapon)
//{
//	if (heldWeapon)
//	{
//		heldWeapon->SetChildActorClass(weapon.weaponSubclass);
//		
//		AActor* weaponActor = heldWeapon->GetChildActor();
//		AWeapon* myWeapon = Cast<AGun>(weaponActor);
//
//		if (myWeapon)
//		{
//			myWeapon->SetReserveAmmo(weapon.reserveAmmo);
//			myWeapon->SetAmmoInClip(weapon.ammoInClip);
//		}
//	}
//}

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

//void AMyPlayerCharacter::TakeDamage(int damage)
//{
//	//Could pass in a damage type later so the actor can respond differently
//
//	health->TakeDamage(damage);
//
//	if (health->GetCurrentHp() <= 0)
//	{
//		//End the game
//		KillPlayer();
//	}
//}

//void AMyPlayerCharacter::RestoreHp(int hp)
//{
//	UE_LOG(LogTemp, Warning, TEXT("Current HP Before Heal: %d"), health->GetCurrentHp());
//
//	health->RestoreHp(hp);
//
//	UE_LOG(LogTemp, Warning, TEXT("Current HP After Heal: %d"), health->GetCurrentHp());
//}

void AMyPlayerCharacter::RestoreAmmo(FName ammoType, int ammo)
{
	weaponArsenal->AddAmmo(ammoType, ammo);
}
