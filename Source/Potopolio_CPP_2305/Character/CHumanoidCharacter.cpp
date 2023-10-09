// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CHumanoidCharacter.h"
#include "Interface/BowInterface.h"
#include "GameFramework/CharacterMovementComponent.h"


ACHumanoidCharacter::ACHumanoidCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACHumanoidCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
}

void ACHumanoidCharacter::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	SpawnParameters.Instigator = this;

	for (auto& WeaponClass : WeaponClasses)
	{
		if (!WeaponClass)
			break;
		FAttachmentTransformRules const Rules(EAttachmentRule::SnapToTarget, true);
		auto* const SpawnedWeapon = GetWorld()->SpawnActor<ACWeapon>(WeaponClass, SpawnParameters);
		SpawnedWeapon->AttachToComponent(GetMesh(), Rules, SpawnedWeapon->GetSocketName());
		Weapons.Add(SpawnedWeapon);
		Cast<IWeaponInterface>(SpawnedWeapon)->SetDamage(BaseDamage);
		MaxWeaponIndex++;
	}

	if (Weapons.Num() > CurWeaponIndex)
	{
		Weapon = Weapons[CurWeaponIndex];
		Weapon->SetVisiblity(true);
	}
}

void ACHumanoidCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Weapon->GetWeaponType() == EWeaponType::Bow)
	{
		if (auto* Bow = Cast<IBowInterface>(Weapon))
		{
			CurBowState = Bow->GetBowState();
			

			if (IsWalking)
				GetCharacterMovement()->MaxWalkSpeed = UKismetMathLibrary::Lerp(GetCharacterMovement()->MaxWalkSpeed, SpeedWalk, 0.01f);
			else
			{
				GetCharacterMovement()->MaxWalkSpeed = UKismetMathLibrary::Lerp(GetCharacterMovement()->MaxWalkSpeed, SpeedMax, 0.01f);
				if (CurBowState != EBowState::Idle)
					GetCharacterMovement()->MaxWalkSpeed = UKismetMathLibrary::Lerp(GetCharacterMovement()->MaxWalkSpeed, SpeedWalk, 0.01f);
			}
			

		}
	}
	else
		CurBowState = EBowState::Idle;

}

const EElements ACHumanoidCharacter::GetElementType()
{
	if (!Weapon)
	{
		if (CurMagicSpell == EMagics::None)
			return EElements::None;
		else
			return ElementType;
	}
	else
	{
		if (CurMagicSpell == EMagics::None)
			return Weapon->GetElementType();
		else
			return ElementType;
	}
}

const EWeaponType ACHumanoidCharacter::GetWeaponType()
{
	if(!Weapon)
		return EWeaponType::None;

	return Weapon->GetWeaponType();
}

const float ACHumanoidCharacter::GetFloatInputDirection()
{
	float Dir = UKismetMathLibrary::Atan2(InputDirection.Y, InputDirection.X);
	return UKismetMathLibrary::RadiansToDegrees(Dir);
}

const FName ACHumanoidCharacter::GetMagicSpawnSocketName()
{
	switch (Weapon->GetWeaponType())
	{
	case EWeaponType::None:
	case EWeaponType::Sword:
		return LHMagicSocket;
		break;
	case EWeaponType::Bow:
		return RHMagicSocket;
		break;
	default:
		break;
	}

	return "None_Name";
}

UClass* ACHumanoidCharacter::GetMagicClass()
{
	switch (CurMagicSpell)
	{
	case EMagics::None:
		break;
	case EMagics::Arrow:
		return MagicArrowClass;
	case EMagics::Circle:
		return MagicStormClass;
	default:
		break;
	}
	return nullptr;
}

void ACHumanoidCharacter::BeginAction1()
{
	if (!CheckAnimMontagePlayable())
		return;

	Action1OrderedIn = true;

}

void ACHumanoidCharacter::EndAction1()
{
	if (!Action1OrderedIn)
		return;

	Action1OrderedIn = false;

	SetAnimMontagePlayable(false);

	if (UMontageFunctionLibrary::PlayAnimMontage(MagicMontageData,
		Weapon->GetWeaponType() == EWeaponType::Bow ? "Right" : "Left", this))
	{
		CurMagicSpell = EMagics::Arrow;
		GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &ThisClass::EndMagicMontage);
	}
}

void ACHumanoidCharacter::BeginAction2()
{
	if (!CheckAnimMontagePlayable())
		return;

	Action2OrderedIn = true;
	//ElementType을 어떻게 할까..
	//Player의 값, Monster의 값. 별도? Notifiy에서 해당 값으로 MagicArrow 변환..
}

void ACHumanoidCharacter::EndAction2()
{
	if (!Action2OrderedIn)
		return;

	Action2OrderedIn = false;

	SetAnimMontagePlayable(false);

	if (UMontageFunctionLibrary::PlayAnimMontage(MagicMontageData,
		Weapon->GetWeaponType() == EWeaponType::Bow ? "Right" : "Left", this))
	{
		CurMagicSpell = EMagics::Circle;
		GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &ThisClass::EndMagicMontage);
	}
}

void ACHumanoidCharacter::BeginAction3()
{
}

void ACHumanoidCharacter::EndAction3()
{
}

void ACHumanoidCharacter::BeginAction4()
{
}

void ACHumanoidCharacter::EndAction4()
{
}

void ACHumanoidCharacter::EndMagicMontage(UAnimMontage* BuffMontage, bool Interrupted)
{
	SetAnimMontagePlayable(true);
	CurMagicSpell = EMagics::None;
	GetMesh()->GetAnimInstance()->OnMontageEnded.RemoveDynamic(this, &ThisClass::EndMagicMontage);

}
 
void ACHumanoidCharacter::BeginActionA()
{
	if (!Weapon)
		return;

	if (!CheckActionPlayable())
		return;

	Weapon->BeginBasicAction();
}

void ACHumanoidCharacter::EndActionA()
{
	if (!Weapon)
		return;

	Weapon->EndBasicAction();
}

void ACHumanoidCharacter::BeginActionB()
{
	if (!Weapon)
		return;

	if (!CheckActionPlayable())
		return;

	Weapon->BeginIntensiveAction();
}

void ACHumanoidCharacter::EndActionB()
{
	if (!Weapon)
		return;

	Weapon->EndIntensiveAction();
}