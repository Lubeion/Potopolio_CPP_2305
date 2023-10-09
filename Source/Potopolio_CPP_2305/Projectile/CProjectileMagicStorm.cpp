// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/CProjectileMagicStorm.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "DamageFunctionLibrary.h"
#include "Character/CCharacter.h"
#include "Logger.h"

ACProjectileMagicStorm::ACProjectileMagicStorm()
{
	StormCollider = CreateDefaultSubobject<UCapsuleComponent>("StormCollider");
	StormCollider->SetupAttachment(RootComponent);
	StormCollider->SetCollisionProfileName("WeaponCollision");
}

void ACProjectileMagicStorm::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	FVector StormLocation = RootComponent->GetRelativeLocation();
	StormLocation.Z += StormCollider->GetScaledCapsuleHalfHeight();
	StormCollider->SetRelativeLocation(StormLocation);

	SetLifeSpan(8.0f);

}

void ACProjectileMagicStorm::BeginPlay()
{
	Super::BeginPlay();

	OnActorEndOverlap.AddDynamic(this, &ThisClass::ColliderEndOverlapped);

	GetWorld()->GetTimerManager().SetTimer(Timer, this, &ThisClass::DamageEvent, DamageInterval, true, 0.0f);
}

void ACProjectileMagicStorm::ColliderEndOverlapped(AActor* OverlappedActor, AActor* OtherActor)
{
	if (Targets.Contains(Cast<ACCharacter>(OtherActor)))
		Targets.Remove(Cast<ACCharacter>(OtherActor));
}


void ACProjectileMagicStorm::DamageEvent()
{
	for (ACCharacter* Target : Targets.Array())
		UDamageFunctionLibrary::ApplyDamage(Target, Cast<ACCharacter>(GetOwner()), Damage * 0.5f, ElementType);
}

void ACProjectileMagicStorm::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

void ACProjectileMagicStorm::VirtualOverlappedEvent(AActor* OtherActor)
{
	if(ACCharacter* OA = Cast<ACCharacter>(OtherActor))
		if (!Targets.Contains(OA))
		{
			Targets.Add(OA);
		}

}
