// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) {
	
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw) {

	if (!ensure(LeftTrack && RightTrack)) { return; }
		//UE_LOG(LogTemp, Warning, TEXT("Intend Forward %f"), Throw);
		LeftTrack->SetThrottle(Throw);
		//UE_LOG(LogTemp, Warning, TEXT("call made Forward %f"), Throw);
		RightTrack->SetThrottle(Throw);
	
}

void UTankMovementComponent::IntendTurnRight(float Throw) {

	if (!ensure(LeftTrack && RightTrack)) { return; }
		//UE_LOG(LogTemp, Warning, TEXT("Turn Left %f"), Throw);
		LeftTrack->SetThrottle(Throw);
		//UE_LOG(LogTemp, Warning, TEXT("Turn right %f"), -Throw);
		RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bFroceMaxSpeed) {
	//No need to call Super as we're replacing functionality

	auto TankName = GetOwner()->GetName();
	auto TankFoward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	
	auto ForwardThrow = FVector::DotProduct(TankFoward, AIForwardIntention);
	IntendMoveForward(ForwardThrow);

	auto RightThrow = FVector::CrossProduct(TankFoward, AIForwardIntention).Z;
	IntendTurnRight(RightThrow);

	//UE_LOG(LogTemp, Warning, TEXT("%s vectoring to %s"), *TankName, *MoveVelocity.ToString());

}