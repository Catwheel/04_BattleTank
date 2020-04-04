// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin play"));

	ATank* tempTank = GetControlledTank();
	if (tempTank != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController controlling %s"), *(tempTank->GetName()));
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("PlayerController NOT controlling a tank!"));
}

void ATankPlayerController::Tick( float DeltaTime )
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; // Out Parameter
	if (GetSightRayHitLocation(HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
			// TODO: tell controlled tank to aim at this point
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLoc) const
{
	HitLoc = FVector(1.0);
	return true;
	/*
	// cast a ray towards the mouse cursor with a definite length.
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(OUT Hit, PlayerViewPointLocation, LineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParameters);
	// where the ray hits, make the hitloc that position
	HitLoc = Hit.Location;
	// if it hit something, return bool;
	return (Hit.Actor);*/
}