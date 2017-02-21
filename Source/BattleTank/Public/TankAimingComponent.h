// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Enum for aiming state
UENUM()
enum class EFiringState : uint8 {
	Reloading, Aiming, Locked, OutOfAmmo
};


// Forward Declaration
class UTankBarrel; 
class UTankTurret;
class AProjectile;

// Hods barrel's properties and Elevate Method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	void AimAt(FVector);
	EFiringState GetFiringState() const;

	UFUNCTION(BlueprintCallable, Category = "Firing")
		void Fire();
	UFUNCTION(BlueprintCallable, Category = "Firing")
		int32 GetAmmoRemaining() const;

protected:
	UPROPERTY(BlueprintReadonly, Category = "State")
		EFiringState FiringState = EFiringState::Reloading;
	

private:
	// Sets default values for this component's properties
	UTankAimingComponent();
	void BeginPlay();

	bool IsBarrelMoving();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	void MoveBarrelTowards();
	void MoveTurretTowards();

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 100000;
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeSeconds = 4;
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		int32 Ammo = 10;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint;

	
	double LastFireTime = 0;
	FVector AimDirection;
	
};
