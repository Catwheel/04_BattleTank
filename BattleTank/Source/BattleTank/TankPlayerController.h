// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;
class UTankAimingComponent;

/**
 * Resonsible for helping the player tank aim
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank* GetControlledTank() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimCompRed);
private:
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	float CrosshairXLocation = 0.5;
	UPROPERTY(EditDefaultsOnly)
	float CrosshairYLocation = 0.33333;
	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange= 1000000.f;

	// Start the barrel moving so that a shot would hit where the crosshair intersects the world
	void AimTowardsCrosshair();
	// Cast a ray and return where you hit something or not
	bool GetSightRayHitLocation( FVector& HitLoc ) const;

	bool GetLookDirection( FVector2D ScreenLocation, FVector& LookDirection ) const;

	bool GetLookVectorHitLocation( FVector LookVector, FHitResult& OutHit ) const;
};
