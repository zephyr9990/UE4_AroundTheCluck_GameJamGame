// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerGun.h"
#include "Components/ArrowComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "TimerManager.h"


// Sets default values
APlayerGun::APlayerGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BulletsPerSecond = 2;

	Firing = false;
	ProjectileToSpawn = nullptr;
	GunSoundVolumeMultiplier = .6f;
}

// Called when the game starts or when spawned
void APlayerGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UE_LOG(LogTemp, Warning, TEXT("HI"));
}

void APlayerGun::PullTrigger()
{
	if (!Firing)
	{
		Fire();
		float Time = 1 / BulletsPerSecond;
		GetWorld()->GetTimerManager().SetTimer(FiringHandle, this, &APlayerGun::Fire, Time, true);
		Firing = true;
	}
}

void APlayerGun::Fire()
{
	// If there is a spawn point, spawn projectiles there.
	if (ProjectileSpawnPoint && GunSound)
	{
		ShowMuzzleFlash();
		UGameplayStatics::PlaySoundAtLocation(this, GunSound, ProjectileSpawnPoint->GetComponentLocation(), GunSoundVolumeMultiplier);
		FTransform ProjectileSpawnTransform = ProjectileSpawnPoint->GetComponentTransform();
		GetWorld()->SpawnActor<AActor>(ProjectileToSpawn, ProjectileSpawnTransform);
	}
}

void APlayerGun::ReleaseTrigger()
{
	GetWorld()->GetTimerManager().ClearTimer(FiringHandle);
	Firing = false;
}