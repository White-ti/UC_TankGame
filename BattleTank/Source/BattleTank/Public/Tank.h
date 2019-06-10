// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankTurret;
class UTankBarrel;
class UTankAimingComponent;
class AProjectile;
class UTankMovementComponent;
//class UTankTrack;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

	//UFUNCTION(BlueprintCallable, Category = Setup)
	//void SetTrackReference(UTankTrack* TrackToSet);

protected:
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* TankMovementComponent = nullptr;

private:
	// Sets default values for this pawn's properties
	ATank();

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float LaunchSpeed = 10000; //100m/s

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBlueprint;

	float ReloadTimeInSeconds = 3;

	UTankBarrel* Barrel = nullptr; //TODO remove

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	double LastFireTime = 0;
};
