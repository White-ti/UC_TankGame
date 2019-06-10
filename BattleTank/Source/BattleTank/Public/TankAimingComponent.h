// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class AProjectile;

UENUM()
enum class EFiringState : uint8 {
	Reloading,
	Aiming,
	Locked
};

//forward Declaration
class UTankBarrel;
class UTankTurret;

//Hold Parameters for Barrel
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	void AimAt(FVector HitLocation);
	
	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	void MoveBarrel(FVector AimDirection);
	void MoveTurret(FVector AimDirection);
		
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBlueprint;

	float ReloadTimeInSeconds = 3;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		double LastFireTime = 0;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float LaunchSpeed = 10000; //100m/s
};
