// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "BattleTank.h"
#include "GameFramework/Actor.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay() {

	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("AI Controller Begin Play"));

	//auto PlayerTank = GetPlayerTank();
	//if(!PlayerTank){ UE_LOG(LogTemp, Warning, TEXT("AI Cant find human")); }
	//else { UE_LOG(LogTemp, Warning, TEXT("AI Tank is %s"), *(PlayerTank->GetName())); }
}

void  ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto MyTank = GetPawn();

	if (!ensure(PlayerTank && MyTank)) { return; }

		//Move towards player
		MoveToActor(PlayerTank, AcceptanceRadius);
		
		//Aim towards player
		auto AimingComponent = MyTank->FindComponentByClass<UTankAimingComponent>();
		AimingComponent->AimAt(PlayerTank->GetActorLocation());

		if (AimingComponent->GetFiringState() == EFiringState::Locked) {
			AimingComponent->Fire(); //TODO limit firing rate
		}

}