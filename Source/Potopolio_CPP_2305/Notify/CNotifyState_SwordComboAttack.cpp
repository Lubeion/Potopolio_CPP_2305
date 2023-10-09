// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/CNotifyState_SwordComboAttack.h"
#include "Character/CHumanoidCharacter.h"
#include "Interface/SwordInterface.h"

void UCNotifyState_SwordComboAttack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (auto* const Owner = Cast<ACHumanoidCharacter>(MeshComp->GetOwner()))
	{
		Owner->SetActionPlayable(true);
	}
}
void UCNotifyState_SwordComboAttack::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
}

void UCNotifyState_SwordComboAttack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (auto* const Owner = Cast<ACHumanoidCharacter>(MeshComp->GetOwner()))
	{
		Owner->SetActionPlayable(false);

		if (auto* const Weapon = Cast<ISwordInterface>(Owner->GetWeapon()))
		{
			if (Weapon->GetNextComboEnabled())
			{
				Owner->SetAnimMontagePlayable(true);
				Weapon->NextComboAttack();
			}
		}
	}
}
