// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/CNotify_SetWeaponVisiblity.h"
#include "Character/CHumanoidCharacter.h"
#include "Weapon/CWeapon.h"

void UCNotify_SetWeaponVisiblity::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (IsCurWeapon)
	{
		if (ACHumanoidCharacter* Owner = Cast<ACHumanoidCharacter>(MeshComp->GetOwner()))
			if (IWeaponInterface* Weapon = Cast<IWeaponInterface>(Owner->GetWeapon()))
				Weapon->SetVisiblity(SetVisible);
	}
	else
		if (ACHumanoidCharacter* Owner = Cast<ACHumanoidCharacter>(MeshComp->GetOwner()))
			if (IWeaponInterface* Weapon = Cast<IWeaponInterface>(Owner->GetPreWeapon()))
				Weapon->SetVisiblity(SetVisible);

}