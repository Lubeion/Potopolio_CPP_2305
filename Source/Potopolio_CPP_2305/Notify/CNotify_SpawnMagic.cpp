// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/CNotify_SpawnMagic.h"
#include "Character/CHumanoidCharacter.h"
#include "Projectile/CProjectileMagicArrow.h"
#include "Projectile/CProjectileMagicStorm.h"
#include "Logger.h"

void UCNotify_SpawnMagic::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (auto* Inst = Cast<ACHumanoidCharacter>(MeshComp->GetOwner()))
	{
		FActorSpawnParameters params;
		params.Owner = Inst;
		params.Instigator = Inst;
		params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		switch (Inst->GetMagicSpellType())
		{
		case EMagics::None:
			break;
		case EMagics::Arrow:
		{
			FTransform SpawnTransform = MeshComp->GetSocketTransform(Inst->GetMagicSpawnSocketName());
			auto* Arrow = Cast<ACProjectileMagicArrow>(Inst->GetWorld()->SpawnActor(Inst->GetMagicClass(), &SpawnTransform, params));
			Arrow->SetNewEffect(Inst->GetElementType());
			Arrow->SetDamage(Inst->GetDamage());
			break;
		}
		case EMagics::Circle:
		{
			FTransform SpawnTransform = Inst->GetActorSpawnTransform();
			auto Storm = Cast<ACProjectileMagicStorm>(Inst->GetWorld()->SpawnActor(Inst->GetMagicClass(), &SpawnTransform, params));
			Storm->SetNewEffect(Inst->GetElementType());
			Storm->SetDamage(Inst->GetDamage());
			break;
		}
		}
	}
}