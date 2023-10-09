// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/CBaseTrigger.h"
#include "CTrigger_Parkour.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class POTOPOLIO_CPP_2305_API ACTrigger_Parkour : public ACBaseTrigger
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ACTrigger_Parkour();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual const bool TriggableDegree(const FVector& ActorForwardVector) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly)
		class UStaticMeshComponent* Obstacle;
};
