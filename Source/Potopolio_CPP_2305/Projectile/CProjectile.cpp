// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/CProjectile.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "Components/SphereComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Logger.h"
#include "Character/CCharacter.h"
#include "DamageFunctionLibrary.h"

// Sets default values
ACProjectile::ACProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
	//SetRootComponent(RootComponent);
	
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>("ProjectileMesh");
	SetRootComponent(ProjectileMesh);

	HitCollision = CreateDefaultSubobject<USphereComponent>("HitCollision");
	HitCollision->SetCollisionProfileName("WeaponCollision");
	ProjectileEffect = CreateDefaultSubobject<UParticleSystemComponent>("ProjectileEffect");
	DirectionGuide = CreateDefaultSubobject<UArrowComponent>("GuideArrow");

	HitCollision->SetupAttachment(RootComponent, SocketName);
	ProjectileEffect->SetupAttachment(RootComponent, SocketName);
	DirectionGuide->SetupAttachment(RootComponent, RootSocketName);

}

void ACProjectile::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	//FAttachmentTransformRules const Rules(EAttachmentRule::SnapToTarget, true);
	//HitCollision->AttachToComponent(GetRootComponent(), Rules, SocketName);
	//ProjectileEffect->AttachToComponent(GetRootComponent(), Rules, SocketName);
	//DirectionGuide->AttachToComponent(GetRootComponent(), Rules, RootSocketName);

	UElementsFunctionLibrary::SetParticle(ElementProjectileData, ElementType, ProjectileEffect);
	
	HitCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::ColliderOverlapped);
}

// Called when the game starts or when spawned
void ACProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void ACProjectile::DestroyEffect(AActor* Act)
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), UElementsFunctionLibrary::GetParticleSystem(ElementHitEffectData, ElementType), GetActorTransform());
}

void ACProjectile::ColliderOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == GetOwner())
		return;

	if (auto* const DamagedTarget = Cast<ACCharacter>(OtherActor))
	{
		UDamageFunctionLibrary::ApplyDamage(DamagedTarget, Cast<ACCharacter>(GetOwner()), Damage, ElementType);
		VirtualOverlappedEvent(OtherActor);
	}
}

// Called every frame
void ACProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*if (Fired)
		AddMovementInput(DirectionGuide->GetForwardVector());*/
}

void ACProjectile::SetNewEffect(EElements NewElement)
{
	ElementType = NewElement;
	if (NewElement != EElements::None)
	{
		UElementsFunctionLibrary::SetParticle(ElementProjectileData, ElementType, ProjectileEffect);
		ProjectileEffect->SetVisibility(true);
	}
	else
	{
		ProjectileEffect->SetVisibility(false);
	}
}

void ACProjectile::FireProjectile(FQuat Direction)
{
	//SetActorRotation(Direction);
	Fired = true;
	SetLifeSpan(LifeSpanAfterFired);
	FDetachmentTransformRules Rules(EDetachmentRule::KeepWorld, true);
	GetOwner()->DetachFromActor(Rules);
}

FQuat ACProjectile::GetDirection()
{
	//return GetActorForwardVector().ToOrientationQuat();
	return GetActorRotation().Quaternion();
}



