// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/CNotifyState_SwordAttack.h"
#include "Character/CHumanoidCharacter.h"
#include "Interface/SwordInterface.h"

void UCNotifyState_SwordAttack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (auto* const Owner = Cast<ACHumanoidCharacter>(MeshComp->GetOwner()))
	{
		if (Owner->GetWeaponType() == EWeaponType::Sword)
		{
			if (auto* const ISword = Cast<ISwordInterface>(Owner->GetWeapon()))
			{
				ISword->ActivateAttack(true);
			}
		}
	}
}

void UCNotifyState_SwordAttack::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
}

void UCNotifyState_SwordAttack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (auto* const Owner = Cast<ACHumanoidCharacter>(MeshComp->GetOwner()))
	{
		if (Owner->GetWeaponType() == EWeaponType::Sword)
		{
			if (auto* const ISword = Cast<ISwordInterface>(Owner->GetWeapon()))
			{
				ISword->ActivateAttack(false);
			}
		}
	}
}
