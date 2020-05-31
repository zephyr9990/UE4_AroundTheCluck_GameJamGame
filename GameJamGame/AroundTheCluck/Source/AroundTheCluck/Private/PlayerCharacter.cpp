// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "PlayerGun.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"


APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerGunToSpawn = nullptr;
	PlayerGun = nullptr;
	bCanShoot = true;
	bCameraClamped = false;

	XAxisMin = 0.0f;
	XAxisMax = 0.0f;
	YAxisMin = 0.0f;
	YAxisMax = 0.0f;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerGunToSpawn)
	{
		// Spawn gun
		FTransform GunSpawnTransform = GetMesh()->GetComponentTransform();
		PlayerGun = GetWorld()->SpawnActor<APlayerGun>(PlayerGunToSpawn, GunSpawnTransform);

		// Attach to gun socket.
		const USkeletalMeshSocket* GunSocket = GetMesh()->GetSocketByName("GunSocket");
		GunSocket->AttachActor(PlayerGun, GetMesh());
	}
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Movement
	PlayerInputComponent->BindAxis("MoveUp", this, &APlayerCharacter::MoveUp);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	// Look Orientation
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis("LookRight", this, &APlayerCharacter::LookRight);
}

void APlayerCharacter::MoveUp(float value)
{
	if (Controller && value)
	{
		FVector Up = FVector(1.0f, 0.0f, 0.0f);
		AddMovementInput(Up, value);
	}
}

void APlayerCharacter::MoveRight(float value)
{
	if (Controller && value)
	{
		FVector Right = FVector(0.0f, 1.0f, 0.0f);
		AddMovementInput(Right, value);
	}
}

void APlayerCharacter::LookUp(float value)
{
	if (Controller)
	{
		FVector Up = FVector(value, 0.0f, 0.0f);
		float RightValue = GetInputAxisValue("LookRight");
		FVector LookDirection = FVector(value, RightValue, 0.0f);
		if (LookDirection.Size() > 0.25f)
		{
			LookInDirection(LookDirection);
			if (bCanShoot)
			{
				PlayerGun->PullTrigger();
			}
		}
		else
		{
			PlayerGun->ReleaseTrigger();
		}
	}
}


void APlayerCharacter::LookRight(float value)
{
	if (Controller)
	{
		FVector Right = FVector(0.0f, value, 0.0f);
		float UpValue = GetInputAxisValue("LookUp");
		FVector LookDirection = FVector(UpValue, value, 0.0f);
		if (LookDirection.Size() > 0.25f)
		{
			LookInDirection(LookDirection);
			if (bCanShoot)
			{
				PlayerGun->PullTrigger();
			}
		}
		else
		{
			PlayerGun->ReleaseTrigger();
		}
	}
}

void APlayerCharacter::LookInDirection(FVector& LookDirection)
{

	FRotator NewRotation = UKismetMathLibrary::MakeRotFromX(LookDirection);
	Controller->SetControlRotation(NewRotation);
}

void APlayerCharacter::ClampCamera(USpringArmComponent* CameraBoom)
{
	if (CameraBoom) 
	{
		FVector CameraBoomLocation = CameraBoom->GetComponentLocation();
		float XClampedValue = UKismetMathLibrary::FClamp(GetActorLocation().X, XAxisMin, XAxisMax);
		float YClampedValue = UKismetMathLibrary::FClamp(GetActorLocation().Y, YAxisMin, YAxisMax);

		FVector ClampedLocation = FVector(XClampedValue, YClampedValue, CameraBoomLocation.Z);
		CameraBoom->SetWorldLocation(ClampedLocation);
	}
}
