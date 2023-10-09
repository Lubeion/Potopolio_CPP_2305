// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile/CProjectile.h"
#include "CProjectileMagicArrow.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class POTOPOLIO_CPP_2305_API ACProjectileMagicArrow : public ACProjectile
{
	GENERATED_BODY()
	
public:
	ACProjectileMagicArrow();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetNewEffect(EElements NewElement) override;
	virtual void FireProjectile(FQuat Direction) override;

private:
	void VirtualOverlappedEvent(AActor* OtherActor) override;

protected:
	UPROPERTY(EditDefaultsOnly)
		class UProjectileMovementComponent* ProjectileMovement;
};
