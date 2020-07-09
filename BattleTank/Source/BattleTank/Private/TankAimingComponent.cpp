// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	TankBarrel = BarrelToSet;
	TankTurret = TurretToSet;
}

void UTankAimingComponent::SetTankBarrelRef(UTankBarrel* BarrelToSet)
{
	if (!ensure(BarrelToSet)) { return; }
	TankBarrel = BarrelToSet;
}

void UTankAimingComponent::SetTankTurretRef(UTankTurret* TurretToSet)
{
	if (!ensure(TurretToSet)) { return; }
	TankTurret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector Location, float LaunchSpeed)
{
	if (!ensure(TankBarrel)) { return; }
	FVector OutLaunchVelocity(0);
	FVector StartLocation = TankBarrel->GetSocketLocation(FName("Projectile"));

	// Calculate the outLaunchVelocity
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, Location, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace);
	if (bHaveAimSolution)
	{
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(TankBarrel && TankTurret)) { return; }
	auto BarrelRotation = TankBarrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotation;
	// Rotate the barrel to face the aimdirection
	TankBarrel->Elevate(DeltaRotator.Pitch);
	TankTurret->Rotate(DeltaRotator.Yaw);
	// if the amount of rotation needed is more than some variable "TurningSpeed", only rotate the barrel up to the turning speed amount

}