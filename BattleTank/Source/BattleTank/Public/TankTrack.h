// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack used to set maximum driving force and tank movement
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);
	
	//Max force per track in newtons
	UPROPERTY(EditDefaultsOnly)
		float TrackMaxDrivingForce = 10000000; //Assume 40 tonne tank, 1g acceleration

private:
	UTankTrack();

	TArray<class ASprungWheel*> GetWheels() const;

	//UFUNCTION()
	//void OnHit(UPrimitiveComponent* HitComponent, AActor * OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult & Hit);

	//virtual void BeginPlay() override;

	//void ApplySideWaysForce();

	void DriveTrack(float CurrentThrottle);

};


