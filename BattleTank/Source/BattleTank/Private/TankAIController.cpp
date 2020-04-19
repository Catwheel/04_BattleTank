// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"




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

	ATank* tempPCTank = GetPlayerTank();
	if (tempPCTank != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found Player Tank %s"), *(tempPCTank->GetName()));
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("No found Player Tank!"));
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ATank* MyTank = GetControlledTank();
	if (MyTank)
	{
		ATank* PlayerTank = GetPlayerTank();
		if (PlayerTank)
		{
			MyTank->AimAt(PlayerTank->GetActorLocation());
		}
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto tempPC = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!tempPC) { return nullptr; }
	return Cast<ATank>(tempPC);
}