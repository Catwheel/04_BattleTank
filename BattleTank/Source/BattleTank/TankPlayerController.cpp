// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

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

	// Get world location through crosshair using linetrace
	// If it hits the landscape
		// tell controlled tank to aim at this point
}