// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet) {
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet) {
	Turret = TurretToSet;
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) {
	if (!Barrel) { return; }
	if (!Turret) { return; }

	FVector OutLaunchVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	if (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace)) {
		auto OurTankName = GetOwner()->GetName();
		auto BarrelLocation = Barrel->GetComponentLocation().ToString();
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		//auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f: %s aiming at: %s  from %s"), Time, *OurTankName, *(AimDirection.ToString()), *BarrelLocation);
		MoveBarrel(AimDirection);
		MoveTurret(AimDirection);
	}
	else {
		//auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f: No Solution"), Time);
	}
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	//Work out the difference between current and aimdirection and move in 1 tick towards it
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimRotation = AimDirection.Rotation();
	auto DeltaRotation = AimRotation - BarrelRotation;
	//UE_LOG(LogTemp, Warning, TEXT("Tank %s, Aim %s, Barrel %s, Delta %s"), *GetOwner()->GetName(), *AimRotation.ToString(), *BarrelRotation.ToString(), *DeltaRotation.ToString());

	Barrel->Elevate(DeltaRotation.Pitch);
}

void UTankAimingComponent::MoveTurret(FVector AimDirection)
{
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimRotation = AimDirection.Rotation();
	auto DeltaRotation = AimRotation - BarrelRotation;

	Turret->Rotate(DeltaRotation.Yaw);
}

