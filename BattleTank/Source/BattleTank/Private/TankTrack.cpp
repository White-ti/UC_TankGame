// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
#include "SprungWheel.h"
#include "SpawnPoint.h"

//void UTankTrack::BeginPlay() {
	//Super::BeginPlay();
	//OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
//}

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = false;
	SetNotifyRigidBodyCollision(true);
}

TArray<class ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<ASprungWheel*> ResultArray;
	TArray<USceneComponent*> Children;
	GetChildrenComponents(true, Children);
	for (USceneComponent* Child : Children) {
		auto SpawnPointChild = Cast<USpawnPoint>(Child);
		if (!SpawnPointChild) continue;

		AActor* SpawnedChild = SpawnPointChild->GetSpawnedActor();
		auto SprungWheel = Cast<ASprungWheel>(SpawnedChild);
		if (!SprungWheel) continue;

		ResultArray.Add(SprungWheel);
	}

	return ResultArray;

}

//void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
//	DriveTrack();
//	ApplySideWaysForce();
//	CurrentThrottle = 0;
//}
//
//void UTankTrack::ApplySideWaysForce() {
//	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
//	auto DeltaTime = GetWorld()->GetDeltaSeconds();
//	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
//	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
//	auto CorrectionForce = TankRoot->GetMass() * CorrectionAcceleration / 2;
//	TankRoot->AddForce(CorrectionForce);
//}

void UTankTrack::SetThrottle(float Throttle) {

	//auto TankName = GetOwner()->GetName();
	//auto Name = GetName();
	//UE_LOG(LogTemp, Warning, TEXT("Tank %s, Throttle %s  moving at %f"), *TankName, *Name, Throttle);

	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1, 1);
	DriveTrack(CurrentThrottle);
}

void UTankTrack::DriveTrack(float CurrentThrottle) {
	auto ForceApplied = CurrentThrottle * TrackMaxDrivingForce;
	//auto ForceLocation = GetComponentLocation();
	//auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	//TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
	auto Wheels = GetWheels();
	auto ForcePerWheel = ForceApplied / Wheels.Num();
	for (ASprungWheel* Wheel: Wheels) {
		Wheel->AddDrivingForce(ForcePerWheel);
	}
}