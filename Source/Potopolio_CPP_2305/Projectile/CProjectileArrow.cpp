// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/CProjectileArrow.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Character/CCharacter.h"
#include "DamageFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "Logger.h"

ACProjectileArrow::ACProjectileArrow()
{
	Movement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	Trail = CreateDefaultSubobject<UParticleSystemComponent>("Trail");
}

void ACProjectileArrow::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	Movement->bSimulationEnabled = false;
}

void ACProjectileArrow::BeginPlay()
{
	Super::BeginPlay();
}

void ACProjectileArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACProjectileArrow::SetNewEffect(EElements NewElement)
{
	Super::SetNewEffect(NewElement);
	ProjectileEffect->SetWorldScale3D(FVector(0.1f, 0.1f, 0.1f));
}

void ACProjectileArrow::SetVisiblity(bool IsVisible)
{
	ProjectileMesh->SetVisibility(IsVisible);
	ProjectileEffect->SetVisibility(IsVisible);
}

void ACProjectileArrow::FireProjectile(FQuat Direction)
{
	Super::FireProjectile(Direction);
	
	Movement->Velocity = Direction.GetRightVector() * 3000;
	Movement->bSimulationEnabled = true;
	Trail->BeginTrails(TrailSocketStart, TrailSocketEnd, ETrailWidthMode::ETrailWidthMode_FromCentre, 5.0f);
}

void ACProjectileArrow::VirtualOverlappedEvent(AActor* OtherActor)
{
	Movement->bSimulationEnabled = false;
	HitCollision->SetGenerateOverlapEvents(false);

	if (auto* const OtherCharacter = Cast<ACCharacter>(OtherActor))
	{
		if (OtherCharacter->GetShieldCount() > 0)
			AttachToComponent(Cast<ACCharacter>(OtherActor)->GetShieldMesh(), FAttachmentTransformRules::KeepWorldTransform);
		else
		{
			FName ClosestSocketName =
				OtherCharacter->GetMesh()->FindClosestBone(GetActorLocation());
			AttachToComponent(Cast<ACCharacter>(OtherActor)->GetMesh(), FAttachmentTransformRules::KeepWorldTransform, ClosestSocketName);
		}
	}

}
