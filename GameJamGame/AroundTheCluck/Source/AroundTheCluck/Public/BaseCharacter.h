// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class AROUNDTHECLUCK_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Base Character")
		float Health = 100;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Base Character")
		bool bIsDead = false;


	UFUNCTION(BlueprintCallable, Category = "Base Character")
	/** Returns whether or not the character is dead.
	* @return Where the character is dead or not.
	*/
	virtual void CalculateDead();

	UFUNCTION(BlueprintCallable, Category = "Base Character")
	/** Subtracts the amount of damage taken from health.
	* @param DamageAmount - The amount of damage to be received by this character.
	*/
	virtual void CalculateHealth(float DamageAmount);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
