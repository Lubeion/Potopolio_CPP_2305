// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/CNotify_SetArrowCondition.h"
#include "Interface/BowInterface.h"
#include "Interface/WeaponInterface.h"
#include "Character/CHumanoidCharacter.h"
#include "Projectile/CProjectileArrow.h"
#include "Logger.h"

void UCNotify_SetArrowCondition::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	//ȭ�� �����/���̱� (������, �߻�), ȭ�� �Ӽ� ����(��æƮ) ��Ƽ����
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