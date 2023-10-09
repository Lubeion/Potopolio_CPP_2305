// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/CSword.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "DamageFunctionLibrary.h"

ACSword::ACSword()
{
	PrimaryActorTick.bCanEverTick = true;
		

	ElementEffect = CreateDefaultSubobject<UParticleSystemComponent>("ElementEffect");
	ElementEffect->SetAutoActivate(false);

	SwordCollision = CreateDefaultSubobject<UCapsuleComponent>("SwordCollision");
	SwordCollision->SetCollisionProfileName("WeaponCollision", false);

	Trail = CreateDefaultSubobject<UParticleSystemComponent>("Trail");

	Damage = 10;
	
}

void ACSword::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	if (ElementType != EElements::None)
		UElementsFunctionLibrary::SetParticle(ElementParticleData, ElementType, ElementEffect);
	WeaponType = EWeaponType::Sword;

	FAttachmentTransformRules const Rules(EAttachmentRule::SnapToTarget, true);

	ElementEffect->AttachToComponent(GetRootComponent(), Rules, AttachEffectSocketName);
	SwordCollision->AttachToComponent(GetRootComponent(), Rules, AttachEffectSocketName);
	SwordCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::BeginOverlap);
	SwordCollision->OnComponentEndOverlap.AddDynamic(this, &ThisClass::EndOverlap);
}

void ACSword::BeginPlay()
{
	Super::BeginPlay();
	Trail->BeginTrails(TrailSocketStart, TrailSocketEnd, ETrailWidthMode::ETrailWidthMode_FromCentre, 2.0f);
	Trail->Deactivate();
}

void ACSword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Enchanted)
	{
		EnchantDuration -= DeltaTime;
		if (EnchantDuration <= 0)
		{
			ElementType = EElements::None;
			SetNewElementVisuality();
			Enchanted = false;
		}
	}

}

void ACSword::SetNewElementVisuality()
{
	Super::SetNewElementVisuality();
	UElementsFunctionLibrary::SetParticle(ElementParticleData, ElementType, ElementEffect);

	if (ElementType != EElements::None)
		ElementEffect->Activate(true);
	else
		ElementEffect->Deactivate();

}

void ACSword::BeginElementAction()
{
	//Element Function에 visualize UI관련 만들고 띄우기.
	if (ACCharacter* Inst = Cast<ACCharacter>(GetInstigator()))
	{
		if (Inst->GetSimpleState() == ESimpleState::Dead)
			return;

		if(Inst->CheckActionPlayable())
			ElementOrderedIn = true;
	}
}

bool ACSword::EndElementAction(const FVector2D& InMousePos)
{
	if (!ElementOrderedIn)
		return false;

	ElementOrderedIn = false;

	if (!UElementsFunctionLibrary::SelectElement(ElementType, InMousePos))
		return false;

	//UI 끄기
	if (ElementType != EElements::None)
	{

		if (ACCharacter* Inst = Cast<ACCharacter>(GetInstigator()))
		{
			if (Inst->CheckAnimMontagePlayable())
			{
				if (UMontageFunctionLibrary::PlayAnimMontage(MontageData, "Buff", GetInstigator()))
				{
					Inst->GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &ThisClass::ChangeElementEffect);
					Inst->SetAnimMontagePlayable(false);
					return true;
				}
			}
		}
	}

	return false;

}

void ACSword::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != GetInstigator())
	{
		if (auto* const Target = Cast<ACCharacter>(OtherActor))
		{
			if (!Targets.Contains(Target))
			{
				Targets.Add(Target);
				UDamageFunctionLibrary::ApplyDamage(Cast<ACCharacter>(OtherActor), Cast<ACCharacter>(GetInstigator()), Damage, ElementType);
			}
		}
	}
}

void ACSword::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void ACSword::ActivateAttack(bool Activate)
{
	SwordCollision->SetGenerateOverlapEvents(Activate);
	Trail->SetActive(Activate);

	if (!Activate)
		Targets.Empty();
}

void ACSword::BeginComboAttack()
{
	if (ACCharacter* Inst = Cast<ACCharacter>(GetInstigator()))
	{
		if (Inst->GetSimpleState() == ESimpleState::Dead)
			return;

		if (Inst->CheckActionPlayable())
		{
			ComboAttackOrderedIn = true;
		}
	}
}

void ACSword::EndComboAttack()
{
	if (!ComboAttackOrderedIn)
		return;

	ComboAttackOrderedIn = false;


	if (ACCharacter* Inst = Cast<ACCharacter>(GetInstigator()))
	{
		if (Inst->CheckAnimMontagePlayable())
		{
			Inst->SetSimpleStateBattle();

			if (UMontageFunctionLibrary::PlayAnimMontage(MontageData, ComboCount, GetInstigator()))
			{
				Inst->GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &ThisClass::EndAttackMontage);
				Inst->SetAnimMontagePlayable(false);
			}
		}
		else
		{
			if (Inst->CheckActionPlayable())
			{
				if (ComboCount < 1)
				{
					ComboCount++;
					Inst->SetActionPlayable(false);
					NextComboAttackEnabled = true;
				}
			}
		}
	}
}

void ACSword::BeginPowerAttack()
{
	if (ACCharacter* Inst = Cast<ACCharacter>(GetInstigator()))
	{
		if (Inst->GetSimpleState() == ESimpleState::Dead)
			return;

		if (Inst->CheckActionPlayable())
		{
			PowerAttackOrderedIn = true;
		}
	}
}

void ACSword::EndPowerAttack()
{
	if (!PowerAttackOrderedIn)
		return;

	PowerAttackOrderedIn = false;

	if (ACCharacter* Inst = Cast<ACCharacter>(GetInstigator()))
	{
		if (Inst->CheckAnimMontagePlayable())
		{
			Inst->SetSimpleStateBattle();

			if (UMontageFunctionLibrary::PlayAnimMontage(MontageData, "PowerAttack", GetInstigator()))
			{
				Inst->GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &ThisClass::EndAttackMontage);
				Inst->SetAnimMontagePlayable(false);
			}
		}
	}
}

void ACSword::NextComboAttack()
{
	if (!NextComboAttackEnabled)
		return;

	if (ACCharacter* Inst = Cast<ACCharacter>(GetInstigator()))
	{
		if (Inst->GetSimpleState() == ESimpleState::Dead ||
			(int)Inst->GetBattleState() >= 2)
			return;

		Inst->SetSimpleStateBattle();

		if (Inst->CheckAnimMontagePlayable())
		{
			if (UMontageFunctionLibrary::PlayAnimMontage(MontageData, ComboCount, GetInstigator()))
			{
				Inst->SetAnimMontagePlayable(false);
			}
		}
	}

	NextComboAttackEnabled = false;
}



void ACSword::EndAttackMontage(UAnimMontage* AttackMontage, bool Interrupted)
{
	if (ACCharacter* Inst = Cast<ACCharacter>(GetInstigator()))
	{
		ComboCount = 0;
		NextComboAttackEnabled = false;

		if(Inst->GetBattleState() >= EBattleState::Break)
			Inst->GetMesh()->GetAnimInstance()->OnMontageEnded.RemoveDynamic(this, &ThisClass::EndAttackMontage);

		if (Interrupted)
			return;

		Inst->GetMesh()->GetAnimInstance()->OnMontageEnded.RemoveDynamic(this, &ThisClass::EndAttackMontage);
		Inst->SetAnimMontagePlayable(true);
	}

}

void ACSword::ChangeElementEffect(UAnimMontage* BuffMontage, bool Interrupted)
{
	if (ACCharacter* Inst = Cast<ACCharacter>(GetInstigator()))
	{

		Inst->GetMesh()->GetAnimInstance()->OnMontageEnded.RemoveDynamic(this, &ThisClass::ChangeElementEffect);

		if (Inst->GetSimpleState() == ESimpleState::Dead)
			return;
		if (Interrupted)
			return;

		Inst->SetAnimMontagePlayable(true);
		SetNewElementVisuality();
		EnchantDuration = 10.0f;
		Enchanted = true;
	}
	
}
