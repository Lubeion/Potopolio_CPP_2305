// Fill out your copyright notice in the Description page of Project Settings.


#include "MontageFunctionLibrary.h"
#include "Character/CCharacter.h"

bool UMontageFunctionLibrary::PlayAnimMontage(const UDataTable* Data, const int Number, APawn* Instigator)
{
	if (Data != nullptr)
	{
		TArray<FMontageData const*> Rows;
		Data->GetAllRows("", Rows);

		const FMontageData* MontageData = Rows[Number];

		if (ACCharacter* Inst = Cast<ACCharacter>(Instigator))
		{
			Inst->PlayAnimMontage(MontageData->Montage, MontageData->PlayRate, MontageData->StartingSection);
			
			return true;// ¸ùÅ¸ÁÖ notifiy.. delegate?
		}
	}
	return false;
}

bool UMontageFunctionLibrary::PlayAnimMontage(const UDataTable* Data, FName RowName, APawn* Instigator)
{
	if (Data != nullptr)
	{
		if (const FMontageData* MData = Data->FindRow<FMontageData>(RowName, ""))
		{
			if (ACCharacter* Inst = Cast<ACCharacter>(Instigator))
			{
				Inst->PlayAnimMontage(MData->Montage, MData->PlayRate, MData->StartingSection);

				return true;
			}
		}
	}
	return false;
}

bool UMontageFunctionLibrary::PlayBowAnimMontage(const UDataTable* Data, FName RowName, IWeaponInterface* Weapon)
{
	if (Data != nullptr)
	{
		if (const FMontageData* MData = Data->FindRow<FMontageData>(RowName, ""))
		{
			if(auto* SK_Weapon = Weapon->GetSKMesh())
			{
				UAnimInstance* AnimInstance = (SK_Weapon) ? SK_Weapon->GetAnimInstance() : nullptr;
				if (MData->Montage && AnimInstance)
				{
					float const Duration = AnimInstance->Montage_Play(MData->Montage, MData->PlayRate);

					if (Duration > 0.f)
					{
						if (MData->StartingSection != NAME_None)
						{
							AnimInstance->Montage_JumpToSection(MData->StartingSection, MData->Montage);
						}
					}
				}
				return true;
			}
		}
	}
	return false;
}