// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "TankBarrel.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	auto TankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s CHICKENL Tank C++ Consturct"), *TankName);
}

void ATank::BeginPlay()
{
	auto TankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s CHICKENL Tank C++ BeginPlay"), *TankName);
}

void ATank::AimAt(FVector Location)
{
	if (!TankAimingComponent) { return; }
	TankAimingComponent->AimAt(Location,LaunchSpeed);
}

void ATank::Fire()
{
	bool isReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) >= ReloadTimeInSeconds;
	if (Barrel && isReloaded) {
		if (!ProjectileBlueprint) { return; }
		// Spawn a projectile at the socket location on the barrel
		FVector BarrelLocation = Barrel->GetSocketLocation(FName("Projectile"));
		FRotator BarrelRotation = Barrel->GetSocketRotation(FName("Projectile"));
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, BarrelLocation, BarrelRotation);
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
	}
}