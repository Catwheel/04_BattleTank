// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetTankBarrelRef(UTankBarrel* BarrelToSet)
{
	TankBarrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector Location, float LaunchSpeed)
{
	if (!TankBarrel) { return; }
	FVector OutLaunchVelocity(0);
	FVector StartLocation = TankBarrel->GetSocketLocation(FName("Projectile"));

	// Calculate the outLaunchVelocity
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, Location, LaunchSpeed);
	if (bHaveAimSolution)
	{
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	auto BarrelRotation = TankBarrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotation;
	// Rotate the barrel to face the aimdirection
	TankBarrel->Elevate(5.f); // TODO: remove magic number
	// if the amount of rotation needed is more than some variable "TurningSpeed", only rotate the barrel up to the turning speed amount

}