// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}

void UTankAimingComponent::BeginPlay()
{
	// So that first fire is after reload
	LastFireTime = GetWorld()->GetTimeSeconds();

	//Probably need this. The Tutor didn't put this in
	Super::BeginPlay();
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	TankBarrel = BarrelToSet;
	TankTurret = TurretToSet;
	AimDirection = FVector::UpVector;
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if ((GetWorld()->GetTimeSeconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}

	// TODO Handle Aiming and locked states

	//Probably need this. The Tutor didn't put this in
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(TankBarrel)) { return false; }

	auto BarrelForward = TankBarrel->GetForwardVector();
	return !AimDirection.Equals(BarrelForward, 0.01f);
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

void UTankAimingComponent::AimAt(FVector Location)
{
	if (!ensure(TankBarrel)) { return; }
	FVector OutLaunchVelocity(0);
	FVector StartLocation = TankBarrel->GetSocketLocation(FName("Projectile"));

	// Calculate the outLaunchVelocity
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, Location, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace);
	if (bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::Fire()
{
	if (FiringState != EFiringState::Reloading) {
		if (!ensure(TankBarrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }
		// Spawn a projectile at the socket location on the barrel
		FVector BarrelLocation = TankBarrel->GetSocketLocation(FName("Projectile"));
		FRotator BarrelRotation = TankBarrel->GetSocketRotation(FName("Projectile"));
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, BarrelLocation, BarrelRotation);
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector inAimDirection)
{
	if (!ensure(TankBarrel) || !ensure(TankTurret)) { return; }
	auto BarrelRotation = TankBarrel->GetForwardVector().Rotation();
	auto AimAsRotator = inAimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotation;
	// Rotate the barrel to face the aimdirection
	TankBarrel->Elevate(DeltaRotator.Pitch);
	if (FMath::Abs(DeltaRotator.Yaw) > 180)
		TankTurret->Rotate(-DeltaRotator.Yaw);
	else
		TankTurret->Rotate(DeltaRotator.Yaw);
	// if the amount of rotation needed is more than some variable "TurningSpeed", only rotate the barrel up to the turning speed amount

}