// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CCharacter.h"
#include "Components/SphereComponent.h"
#include "DamageFunctionLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Logger.h"


#define CreateDefaultSubObjectAuto(Component) \
	Component = CreateDefaultSubobject<std::remove_reference<decltype(*Component)>::type>(#Component)

// Sets default values
ACCharacter::ACCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetGenerateOverlapEvents(false);
	GetMesh()->SetCollisionProfileName("NoCollision", false);
	GetCapsuleComponent()->SetCollisionProfileName("CharacterCollision");

	CreateDefaultSubObjectAuto(ShieldCollider);
	ShieldCollider->SetSphereRadius(100);
	ShieldCollider->SetupAttachment(GetRootComponent());
	ShieldCollider->SetCollisionProfileName("ShieldCollision");

	CreateDefaultSubObjectAuto(ShieldMesh);
	ShieldMesh->SetStaticMesh(LoadObject<UStaticMesh>(this, TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'")));
	ShieldMesh->SetupAttachment(ShieldCollider);
	ShieldMesh->SetGenerateOverlapEvents(false);
	ShieldMesh->SetCollisionProfileName("NoCollision", false);

}

void ACCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
	//SetShieldMaterial(ElementType);
	UElementsFunctionLibrary::SetMaterialInstance(ElementShieldData, ElementType, ShieldMesh);
}

float ACCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (DamageEvent.DamageTypeClass.Get() == UElementDamageTypeNone::StaticClass())
		Damaged(EElements::None, DamageAmount);
	else if (DamageEvent.DamageTypeClass.Get() == UElementDamageTypeFire::StaticClass())
		Damaged(EElements::Fire, DamageAmount);
	else if (DamageEvent.DamageTypeClass.Get() == UElementDamageTypeEletric::StaticClass())
		Damaged(EElements::Eletric, DamageAmount);
	else if (DamageEvent.DamageTypeClass.Get() == UElementDamageTypeIce::StaticClass())
		Damaged(EElements::Ice, DamageAmount);

	return 0.0f;
}

// Called when the game starts or when spawned
void ACCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void ACCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACCharacter::SetSimpleStateBattle()
{
	SetSimpleState(ESimpleState::Battle);
	GetWorld()->GetTimerManager().ClearTimer(T1Handle);
	GetWorld()->GetTimerManager().SetTimer(T1Handle, FTimerDelegate::CreateUObject(this, &ThisClass::SetSimpleStateIdle), BattleModeEndDelay, false);

}

bool ACCharacter::CheckAnimMontagePlayable()
{
	if (BState < EBattleState::Hit)
		return bCanPlayAnimMontage;
	else
		return false;
}

bool ACCharacter::CheckActionPlayable()
{
	if (BState < EBattleState::Hit)
		return bCanAction;
	else
		return false;
}

void ACCharacter::SetAnimMontagePlayable(bool CanPlay)
{
	bCanPlayAnimMontage = CanPlay;
	bCanAction = CanPlay;
}

void ACCharacter::SetActionPlayable(bool CanPlay)
{
	bCanAction = CanPlay;
}

const FTransform ACCharacter::GetActorSpawnTransform()
{
	FTransform Result = FTransform::Identity;
	Result.SetLocation(SpawnActorLocation);
	return Result;
}

void ACCharacter::Damaged(const EElements& InElementType, const float& Damage)
{
	if (ShieldCount > 0)
	{
		if (InElementType == ElementType)
		{
			ShieldCount--;
			Hp -= Damage * ElementDamageBonus;
		}
		else
			Hp -= Damage * ElementDamagePenalty;

		if (ShieldCount <= 0)
		{
			ShieldMesh->SetVisibility(false);
			SetBattleState(EBattleState::Break);
			ShieldCollider->SetGenerateOverlapEvents(false);
			//hieldCollider->Deactivate();
			//½¯µå ²¨Á³´Âµ¥ È­»ìÀÌ ½¯µå¿¡ ¿À¹ö·¾ µÊ.
			
		}
	}
	else
		Hp -= Damage * ShieldBrokenBonus;

	if (Hp <= 0)
	{
		SState = ESimpleState::Idle;
		BState = EBattleState::Dead;
	}

	HitUpdateFunction();
}
