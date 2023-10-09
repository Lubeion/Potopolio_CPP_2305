// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile/CProjectile.h"
#include "CProjectileArrow.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class POTOPOLIO_CPP_2305_API ACProjectileArrow : public ACProjectile
{
	GENERATED_BODY()

public:
	ACProjectileArrow();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void SetNewEffect(EElements NewElement) override;
	void SetVisiblity(bool IsVisible);
	virtual void FireProjectile(FQuat Direction) override;

protected:
	virtual void VirtualOverlappedEvent(AActor* OtherActor) override;

protected:
	UPROPERTY(EditDefaultsOnly)
		class UParticleSystemComponent* Trail;
	UPROPERTY(EditDefaultsOnly)
		FName TrailSocketStart;
	UPROPERTY(EditDefaultsOnly)
		FName TrailSocketEnd;
	UPROPERTY(EditDefaultsOnly)
		class UProjectileMovementComponent* Movement;
};
