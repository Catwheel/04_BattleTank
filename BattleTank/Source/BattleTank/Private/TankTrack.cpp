// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::SetThrottle(float throttle)
{
	// TODO clamp actual throttle value so player can't over-drive
	UE_LOG(LogTemp, Warning, TEXT("%s throttle: %f"), *GetName(), throttle);
}