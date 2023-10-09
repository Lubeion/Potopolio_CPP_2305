// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ElementsFunctionLibrary.h"
#include "Character/CCharacter.h"
#include "DamageFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class POTOPOLIO_CPP_2305_API UDamageFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
		static void ApplyDamage(ACCharacter* Target, ACCharacter* Inst, float Damage, EElements InElementType);
};
