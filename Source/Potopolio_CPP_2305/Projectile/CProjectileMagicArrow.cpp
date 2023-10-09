// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/CProjectileMagicArrow.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Logger.h"

ACProjectileMagicArrow::ACProjectileMagicArrow()
{
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->InitialSpeed = 800.0f;
	ProjectileMovement->ProjectileGravityScale = 0.0f;
	LifeSpanAfterFired = 2.0f;
	
}

void ACProjectileMagicArrow::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	ProjectileMovement->Velocity = GetActorForwardVector();
	
}

void ACProjectileMagicArrow::BeginPlay()
{
	Super::BeginPlay();
	OnDestroyed.AddDynamic(this, &ThisClass::DestroyEffect);
	
}

void ACProjectileMagicArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACProjectileMagicArrow::SetNewEffect(EElements NewElement)
{
	Super::SetNewEffect(NewElement);
}

void ACProjectileMagicArrow::FireProjectile(FQuat Direction)
{
	Super::FireProjectile(Direction);
	ProjectileMovement->Velocity = Direction.Vector();
}

void ACProjectileMagicArrow::VirtualOverlappedEvent(AActor* OtherActor)
{
	HitCollision->SetGenerateOverlapEvents(false);

	Destroy();
}
