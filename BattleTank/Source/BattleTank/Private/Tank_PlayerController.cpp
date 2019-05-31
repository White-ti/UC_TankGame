// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank_PlayerController.h"
#include "BattleTank.h"
#include "Engine/World.h"
#include "Tank.h"

void ATank_PlayerController::BeginPlay() {

	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Player Controller Begin Play"));

	auto ControlledTank = GetControlledTank();
	if(!ControlledTank){ UE_LOG(LogTemp, Warning, TEXT("No Tank")); }
	else { UE_LOG(LogTemp, Warning, TEXT("Player Controller Tank is %s"), *(ControlledTank->GetName())); }

}

void ATank_PlayerController::Tick( float DeltaTime ) {

	Super::Tick( DeltaTime );
	//Aim to crosshair
	AimTowardsCrosshair();

}


ATank* ATank_PlayerController::GetControlledTank() const {
	
	
	return Cast<ATank>(GetPawn());

}

void ATank_PlayerController::AimTowardsCrosshair() {

	if (!GetControlledTank()) { return; }

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation)) {
		//UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *(HitLocation.ToString()));
		GetControlledTank()->AimAt(HitLocation);
	}

}

bool ATank_PlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const {

	// Find crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	// "De-project" the screen position of the cross hair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		//UE_LOG(LogTemp, Warning, TEXT("Look Direction is %s"), *(LookDirection.ToString()));
		GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}

	// Line trace to maximum range
	return true;
}

bool ATank_PlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const {
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}

bool ATank_PlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const {

	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + LookDirection * LineTraceRange;
	if (
			GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility)
			){
		HitLocation = HitResult.Location;
		return true;
	}
	return false;

}