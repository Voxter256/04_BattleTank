// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle) {
	if (GetWorld()->GetRealTimeSeconds() != LastInput) { 
		thisFrameThrottleTotal = 0.f;
	}
	
	if (Throttle + thisFrameThrottleTotal > 1) {
		Throttle = 1 - thisFrameThrottleTotal;
	}
	thisFrameThrottleTotal = Throttle + thisFrameThrottleTotal;
	FVector tempVector;
	float speed;
	GetOwner()->GetVelocity().ToDirectionAndLength(tempVector, speed);
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
	LastInput = GetWorld()->GetRealTimeSeconds();
}


