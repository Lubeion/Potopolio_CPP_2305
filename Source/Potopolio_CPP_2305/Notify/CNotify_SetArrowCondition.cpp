// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/CNotify_SetArrowCondition.h"
#include "Interface/BowInterface.h"
#include "Interface/WeaponInterface.h"
#include "Character/CHumanoidCharacter.h"
#include "Projectile/CProjectileArrow.h"
#include "Logger.h"

void UCNotify_SetArrowCondition::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	//화살 숨기기/보이기 (재장전, 발사), 화살 속성 변경(인챈트) 노티파이
	if (auto* Inst = Cast<ACHumanoidCharacter>(MeshComp->GetOwner()))
	{
		if (auto* Weapon = Inst->GetWeapon())
		{
			if (auto* Bow = Cast<IBowInterface>(Weapon))
			{
				Bow->GetArrowModel()->SetVisiblity(VisibleArrowModel);
				if (SetNewElement)
				{
					Bow->GetArrowModel()->SetNewEffect(Weapon->GetElementType());
				}
				else
				{
					Bow->GetArrowModel()->SetNewEffect(EElements::None);
					Weapon->SetElementType(EElements::None);
				}

			}
		}

	}
}