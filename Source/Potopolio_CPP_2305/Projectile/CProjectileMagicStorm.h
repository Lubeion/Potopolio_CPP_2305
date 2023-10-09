// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile/CProjectile.h"
#include "CProjectileMagicStorm.generated.h"

/**
 * 
 */
class ACCharacter;

UCLASS(Abstract)
class POTOPOLIO_CPP_2305_API ACProjectileMagicStorm : public ACProjectile
{
	GENERATED_BODY()
	
public:
	ACProjectileMagicStorm();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void ColliderEndOverlapped(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
		void DamageEvent();

public:
	virtual void Tick(float DeltaTime) override;

private:
	void VirtualOverlappedEvent(AActor* OtherActor) override;

	
protected:
	UPROPERTY(EditDefaultsOnly)
		class UCapsuleComponent* StormCollider;

	UPROPERTY()
		TSet<class ACCharacter*> Targets;

	FTimerHandle Timer;

private:
	float DamageInterval = 1.0f;

};
