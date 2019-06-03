// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "BattleTank.h"
#include "GameFramework/Actor.h"
#include "Tank.h"

void ATankAIController::BeginPlay() {

	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("AI Controller Begin Play"));

	//auto PlayerTank = GetPlayerTank();
	//if(!PlayerTank){ UE_LOG(LogTemp, Warning, TEXT("AI Cant find human")); }
	//else { UE_LOG(LogTemp, Warning, TEXT("AI Tank is %s"), *(PlayerTank->GetName())); }
}

void  ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto MyTank = Cast<ATank>(GetPawn());

	if (PlayerTank) {

		//Move towards player
		
		//Aim towards player
		MyTank->AimAt(PlayerTank->GetActorLocation());

		//Fire at player
		MyTank->Fire(); //TODO limit firing rate
	}

}