// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"




void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("AIController Begin play"));

	ATank* tempTank = GetControlledTank();
	if (tempTank != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController controlling %s"), *(tempTank->GetName()));
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("AIController NOT controlling a tank!"));
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}