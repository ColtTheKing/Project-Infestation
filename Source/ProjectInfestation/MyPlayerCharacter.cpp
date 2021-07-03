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

	heldGun = CreateDefaultSubobject<UChildActorComponent>(TEXT("HeldGun"));
	heldGun->SetupAttachment(playerArms);

	health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	messageLog = CreateDefaultSubobject<UMessageLogComponent>(TEXT("MessageLog"));
}

// Called when the game starts or when spawned
void AMyPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AMyPlayerCharacter::ReloadWeapon);
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

	/*GetCapsuleComponent()->SetCapsuleHalfHeight(44.0f, true);
	SetActorLocation(GetActorLocation() + FVector(0, 0, -44.0f));
	playerCamera->SetRelativeLocation(playerCamera->GetRelativeLocation() + FVector(0, 0, -44.0f));*/
}

void AMyPlayerCharacter::StopCrouching()
{
	if (bIsCrouched)
		UnCrouch();

	/*GetCapsuleComponent()->SetCapsuleHalfHeight(88.0f, true);
	SetActorLocation(GetActorLocation() + FVector(0, 0, 44.0f));
	playerCamera->SetRelativeLocation(playerCamera->GetRelativeLocation() + FVector(0, 0, 44.0f));*/
}

void AMyPlayerCharacter::Interact()
{
	FHitResult rayHit = ShootRay(interactRange);
	AInteractableActor* hitActor = Cast<AInteractableActor>(rayHit.Actor);

	if (hitActor)
	{
		hitActor->Interact();
	}
}

void AMyPlayerCharacter::FireWeapon()
{
	if (heldGun)
	{
		AActor* gunActor = heldGun->GetChildActor();
		AGun* myGun = Cast<AGun>(gunActor);

		if (myGun)
		{
			myGun->FireGun(this);
		}
	}
}

void AMyPlayerCharacter::ReloadWeapon()
{
	if (heldGun)
	{
		AActor* gunActor = heldGun->GetChildActor();
		AGun* myGun = Cast<AGun>(gunActor);

		if (myGun)
		{
			myGun->ReloadClip();
		}
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

void AMyPlayerCharacter::TakeDamage(int damage)
{
	//Could pass in a damage type later so the actor can respond differently

	health->TakeDamage(damage);

	if (health->GetCurrentHp() <= 0)
	{
		//End the game
		KillPlayer();
	}
}

void AMyPlayerCharacter::RestoreHp(int hp)
{
	UE_LOG(LogTemp, Warning, TEXT("Current HP Before Heal: %d"), health->GetCurrentHp());

	health->RestoreHp(hp);

	UE_LOG(LogTemp, Warning, TEXT("Current HP After Heal: %d"), health->GetCurrentHp());
}

void AMyPlayerCharacter::RestoreAmmo(int ammo)
{
	AActor* gunActor = heldGun->GetChildActor();
	AGun* myGun = Cast<AGun>(gunActor);
	myGun->RestoreAmmo(ammo);
}
