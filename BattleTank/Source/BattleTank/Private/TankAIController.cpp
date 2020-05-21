// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"




void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ATank* MyTank = Cast<ATank>(GetPawn());
	auto TempPC = GetWorld()->GetFirstPlayerController()->GetPawn();
	ATank* PlayerTank = (TempPC ? Cast<ATank>(TempPC): nullptr);
	if (MyTank && PlayerTank)
	{
		MoveToActor(PlayerTank, AcceptedRadius);

		MyTank->AimAt(PlayerTank->GetActorLocation());

		MyTank->Fire(); // TODO limit firing rate
	}
}