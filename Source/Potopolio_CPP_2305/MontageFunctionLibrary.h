// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "Interface/WeaponInterface.h"
#include "MontageFunctionLibrary.generated.h"


/**
 * 
 */

USTRUCT(BlueprintType)
struct FMontageData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere) class UAnimMontage* Montage;
	UPROPERTY(EditAnywhere) float PlayRate = 1.0f;
	UPROPERTY(EditAnywhere) FName StartingSection;
};

UCLASS()
class POTOPOLIO_CPP_2305_API UMontageFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static bool PlayAnimMontage(const UDataTable* Data, const int Number, APawn* Instigator);
	static bool PlayAnimMontage(const UDataTable* Data, FName RowName, APawn* Instigator);
	static bool PlayBowAnimMontage(const UDataTable* Data, FName RowName, IWeaponInterface* Weapon);


};

