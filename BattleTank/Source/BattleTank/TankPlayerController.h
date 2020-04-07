// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATank* GetControlledTank() const;

	virtual void BeginPlay() override;
	virtual void Tick( float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5;
	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.33333;
	UPROPERTY(EditAnywhere)
	float LineTraceRange= 1000000.f;

	// Start the barrel moving so that a shot would hit where the crosshair intersects the world
	void AimTowardsCrosshair();
	// Cast a ray and return where you hit something or not
	bool GetSightRayHitLocation( FVector& HitLoc ) const;

	bool GetLookDirection( FVector2D ScreenLocation, FVector& LookDirection ) const;

	bool GetLookVectorHitLocation( FVector LookVector, FHitResult& OutHit ) const;
};
