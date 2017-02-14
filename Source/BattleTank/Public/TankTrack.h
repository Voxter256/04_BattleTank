// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set the maximum driving force and apply driving forces to the tank.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Input)
		void SetThrottle(float Throttle);
	// Max force per track in Newtons
	UPROPERTY(EditDefaultsOnly)
		float TrackMaxDrivingForce = 2.7 * 40000 * 1.5;
	
private:
	double LastInput = 0;
	float thisFrameThrottleTotal = 0.f;
	
};
