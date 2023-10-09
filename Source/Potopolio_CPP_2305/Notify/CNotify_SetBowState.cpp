// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/CNotify_SetBowState.h"
#include "Character/CHumanoidCharacter.h"
#include "Interface/BowInterface.h"

void UCNotify_SetBowState::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (auto* HOwner = Cast<ACHumanoidCharacter>(MeshComp->GetOwner()))
	{
		if (HOwner->GetWeapon()->GetWeaponType() == EWeaponType::Bow)
		{
			Cast<IBowInterface>(HOwner->GetWeapon())->SetBowState(BowState);
		}
	}
}