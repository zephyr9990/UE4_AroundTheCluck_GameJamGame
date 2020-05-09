// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/KismetMathLibrary.h"


APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
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
	if (Controller && value)
	{
		FVector Up = FVector(value, 0.0f, 0.0f);
		if (Up.Size() > 0.25f)
		{
			float RightValue = GetInputAxisValue("LookRight");
			FVector LookDirection = FVector(value, RightValue, 0.0f);
			FRotator NewRotation = UKismetMathLibrary::MakeRotFromX(LookDirection);
			Controller->SetControlRotation(NewRotation);
		}
	}
}


void APlayerCharacter::LookRight(float value)
{
	if (Controller && value)
	{
		FVector Right = FVector(0.0f, value, 0.0f);
		if (Right.Size() > 0.25f)
		{
			float UpValue = GetInputAxisValue("LookUp");
			FVector LookDirection = FVector(UpValue, value, 0.0f);
			FRotator NewRotation = UKismetMathLibrary::MakeRotFromX(LookDirection);
			Controller->SetControlRotation(NewRotation);
		}
	}
}
