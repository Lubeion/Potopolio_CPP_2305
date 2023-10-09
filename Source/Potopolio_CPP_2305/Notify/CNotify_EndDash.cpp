// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/CNotify_EndDash.h"
#include "Character/CHumanoidCharacter.h"
#include "Logger.h"

void UCNotify_EndDash::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (auto* Owner = Cast<ACHumanoidCharacter>(MeshComp->GetOwner()))
	{
		if (Owner->GetSimpleState() < ESimpleState::Dead)
		{
			Owner->SetBattleState(EBattleState::Idle);
			Owner->SetAnimMontagePlayable(true);
		}
	}
}