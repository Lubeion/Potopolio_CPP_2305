// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Logger.h"

void UDamageFunctionLibrary::ApplyDamage(ACCharacter* Target, ACCharacter* Inst, float Damage, EElements InElementType)
{
	TSubclassOf<UDamageType> DamageType;
	switch (InElementType)
	{
	case EElements::None:
		DamageType = UElementDamageTypeNone::StaticClass();
		break;
	case EElements::Fire:
		DamageType = UElementDamageTypeFire::StaticClass();
		break;
	case EElements::Ice:
		DamageType = UElementDamageTypeIce::StaticClass();
		break;
	case EElements::Eletric:
		DamageType = UElementDamageTypeEletric::StaticClass();
		break;
	case EElements::Max:
		break;
	default:
		break;
	}

	UGameplayStatics::ApplyDamage(Target, Damage, Inst->GetController(), Inst, DamageType);
}
