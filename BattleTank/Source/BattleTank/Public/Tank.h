// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:

	//UFUNCTION(BlueprintCallable, Category = Setup)
	//void SetTrackReference(UTankTrack* TrackToSet);

private:
	// Sets default values for this pawn's properties
	ATank();

};
