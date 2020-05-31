// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "PlayerCharacter.generated.h"

class APlayerGun;
class USpringArmComponent;

/**
 * 
 */
UCLASS()
class AROUNDTHECLUCK_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	APlayerCharacter();

	/** Moves the player upward when the specified axis is moved. 
	* @param value The amount to move.
	*/
	void MoveUp(float value);

	/** Moves the player right when the specified axis is moved.
	* @param value The amount to move.
	*/	
	void MoveRight(float value);

	/** Rotates the player Up when the specified axis is moved.
	* @param value The amount to move.
	*/
	void LookUp(float value);

	/** Rotates the player right when the specified axis is moved.
	* @param value The amount to move.
	*/
	void LookRight(float value);

	/** Rotates the player according to the direction specified in LookUp and LookRight.
	* @param LookDirection - The direction for the player to look.
	*/
	void LookInDirection(FVector& LookDirection);

	/** Clamps the camera of the actor */
	UFUNCTION(BlueprintCallable, Category = "PlayerCharacter")
		void ClampCamera(USpringArmComponent* CameraBoom);

	// The weapon that the player utilizes.
	UPROPERTY(BlueprintReadOnly, Category = "PlayerCharacter")
		APlayerGun* PlayerGun;

	// Tracks whether the player is repairing a fence or not.
	UPROPERTY(BlueprintReadWrite, Category = "PlayerCharacter")
		bool bCanShoot;

	// Whether the camera becomes clamped or not.
	UPROPERTY(BlueprintReadWrite, Category = "PlayerCharacter")
		bool bCameraClamped;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// Gun to spawn and attach to player.
	UPROPERTY(EditAnywhere, Category = "PlayerCharacter")
	TSubclassOf<class APlayerGun> PlayerGunToSpawn;

	// Clamped values;
	UPROPERTY(EditAnywhere, Category = "PlayerCharacter")
		float XAxisMin;

	UPROPERTY(EditAnywhere, Category = "PlayerCharacter")
		float XAxisMax;


	UPROPERTY(EditAnywhere, Category = "PlayerCharacter")
		float YAxisMin;

	UPROPERTY(EditAnywhere, Category = "PlayerCharacter")
		float YAxisMax;
};
