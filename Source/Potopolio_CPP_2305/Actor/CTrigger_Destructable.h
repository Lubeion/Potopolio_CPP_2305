// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/CBaseTrigger.h"
#include "CTrigger_Destructable.generated.h"

/**
 * 
 */
UCLASS()
class POTOPOLIO_CPP_2305_API ACTrigger_Destructable : public ACBaseTrigger
{
	GENERATED_BODY()
	
public:
	// 반응 할 Trigger Actor class 추가 하고, 해당 Trigger에 Activate.. 속성 넣고 체력 파괴시 발동
};
