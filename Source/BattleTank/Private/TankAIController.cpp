// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Tank.h" // So we can impliment OnDeath
#include "TankAIController.h"
// Depends on movement component via pathfinding system

void ATankAIController::SetPawn(APawn* InPawn) {
	Super::SetPawn(InPawn);
	if (InPawn) {
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		//Subscribe to our local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!ensure(PlayerTank && ControlledTank)) { return; }
	
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	//Move towards the Player
	MoveToActor(PlayerTank, AcceptanceRadius);

	//Aim Towards the Player
	AimingComponent->AimAt(PlayerTank->GetActorLocation());
	
	// Fire if ready
	if (AimingComponent->GetFiringState() == EFiringState::Locked) {
		AimingComponent->Fire();
	}

}

void ATankAIController::OnPossessedTankDeath() {
	UE_LOG(LogTemp, Warning, TEXT("Received!"))

	if (!GetPawn()) {	return;	}
	GetPawn()->DetachFromControllerPendingDestroy();
}
