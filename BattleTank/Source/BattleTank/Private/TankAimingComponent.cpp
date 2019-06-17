// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	// ...
}

void UTankAimingComponent::BeginPlay() {
	//first fire after initial reload
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (RoundsLeft <= 0) { FiringState = EFiringState::OutOfAmmo; }
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds) { FiringState = EFiringState::Reloading; }
	else if (IsBarrelMoving()) { FiringState = EFiringState::Aiming; }
	else { FiringState = EFiringState::Locked; }
}

bool UTankAimingComponent::IsBarrelMoving() {
	if (!ensure(Barrel)) { return false; }
	auto BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.01);
}

void UTankAimingComponent::AimAt(FVector HitLocation) {
	if (!ensure(Barrel)) { return; }
	if (!ensure(Turret)) { return; }

	FVector OutLaunchVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	if (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace)) {
		auto OurTankName = GetOwner()->GetName();
		auto BarrelLocation = Barrel->GetComponentLocation().ToString();
		AimDirection = OutLaunchVelocity.GetSafeNormal();
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

	if (FMath::Abs(DeltaRotation.Yaw) < 180) {
		Turret->Rotate(DeltaRotation.Yaw);
	}
	else {
		Turret->Rotate(-DeltaRotation.Yaw);
	}
}

void UTankAimingComponent::Fire() {
	//auto Time = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("%f: Tank Fires"), Time);

	if (FiringState == EFiringState::Locked || FiringState == EFiringState::Aiming) {
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }
		//Spawn a projectile
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Socket")), Barrel->GetSocketRotation(FName("Socket")));

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		RoundsLeft--;
	}
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

int32 UTankAimingComponent::GetRoundsLeft()
{
	return RoundsLeft;
}
