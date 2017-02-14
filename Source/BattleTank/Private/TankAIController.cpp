// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay() {
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());

	if (PlayerTank) {
		//TODO Move towards the Player

		//Aim Towards the Player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		
		// Fire if ready
		ControlledTank->Fire();
		// TODO limit firing rate
	}

}
