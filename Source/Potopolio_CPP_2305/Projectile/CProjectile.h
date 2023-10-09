// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ElementsFunctionLibrary.h"
#include "CProjectile.generated.h"

UCLASS(Abstract)
class POTOPOLIO_CPP_2305_API ACProjectile : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACProjectile();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void DestroyEffect(AActor* Act);

	UFUNCTION()
		void ColliderOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void VirtualOverlappedEvent(AActor* OtherActor) {}

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetNewEffect(EElements NewElement);
	virtual void FireProjectile(FQuat Direction);
	FQuat GetDirection();
	void SetDamage(const float& InDamage) { Damage = InDamage; }

protected:
		//class USceneComponent* RootComponent;

	UPROPERTY(EditDefaultsOnly)
		class UStaticMeshComponent* ProjectileMesh;
	UPROPERTY(EditDefaultsOnly)
		class UParticleSystemComponent* ProjectileEffect;
	UPROPERTY(EditDefaultsOnly)
		class USphereComponent* HitCollision;
	UPROPERTY(EditDefaultsOnly)
		class UDataTable* ElementProjectileData;
	UPROPERTY(EditDefaultsOnly)
		class UDataTable* ElementHitEffectData;
	UPROPERTY(EditDefaultsOnly)
		class UArrowComponent* DirectionGuide;

	UPROPERTY(EditDefaultsOnly)
		EElements ElementType = EElements::None;

	UPROPERTY(EditDefaultsOnly)
		float Speed = 800.0f;
	UPROPERTY(EditDefaultsOnly)
		float Damage;
	UPROPERTY(EditDefaultsOnly)
		float LifeSpanAfterFired = 3.0f;
	UPROPERTY(EditDefaultsOnly)
		FName SocketName = NAME_None;
	UPROPERTY(EditDefaultsOnly)
		FName RootSocketName = NAME_None;

	bool Fired = false;
};
