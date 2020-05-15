// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/Actor.h"
#include "PlayerGun.generated.h"

class UArrowComponent;
class USoundCue;

UCLASS()
class AROUNDTHECLUCK_API APlayerGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerGun();

	// Function that initiates the shooting of projectiles.
	void PullTrigger();

	// Spawns a projectile
	UFUNCTION()
	void Fire();

	// Function that stops spawning projectiles.
	void ReleaseTrigger();

	// Used to keep track of the projectile spawn point.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
		UArrowComponent* ProjectileSpawnPoint;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// The amount of bullets fired per second by this gun.
	UPROPERTY(EditAnywhere, Category = "Player Gun")
	float BulletsPerSecond;

	// Used to see if the player has already started firing.
	bool Firing;

	// Used to keep track of the timer set by PullTrigger().
	FTimerHandle FiringHandle;

	UPROPERTY(EditAnywhere, Category = "Player Gun")
	TSubclassOf<class AActor> ProjectileToSpawn;

	UPROPERTY(EditAnywhere, Category = "Player Gun")
	USoundCue* GunSound; 
};
