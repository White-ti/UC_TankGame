// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "BattleTank.h"
#include "GameFramework/Actor.h"
#include "Tank.h"

void ATankAIController::BeginPlay() {

	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("AI Controller Begin Play"));

	auto PlayerTank = GetPlayerTank();
	if(!PlayerTank){ UE_LOG(LogTemp, Warning, TEXT("AI Cant find human")); }
	else { UE_LOG(LogTemp, Warning, TEXT("AI Tank is %s"), *(PlayerTank->GetName())); }
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }
	return Cast<ATank>(PlayerPawn);
}

ATank* ATankAIController::GetControlledTank() const {

	return Cast<ATank>(GetPawn());
}

void  ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (GetPlayerTank()) {
		//Move towards player
		
		//Aim towards player
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

		//Fire at player
	}

}