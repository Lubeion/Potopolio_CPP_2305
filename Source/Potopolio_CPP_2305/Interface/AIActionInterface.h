// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CCharacter.h"
#include "Actor/CBaseTrigger.h"
#include "UObject/Interface.h"
#include "AIActionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAIActionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class POTOPOLIO_CPP_2305_API IAIActionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void AIActionA() PURE_VIRTUAL(IAIActionInterface::AIActionA, return;)
	virtual void AIActionB() PURE_VIRTUAL(IAIActionInterface::AIActionB, return;)
	virtual void AIAction1() PURE_VIRTUAL(IAIActionInterface::AIAction1, return;)
	virtual void AIAction2() PURE_VIRTUAL(IAIActionInterface::AIAction2, return;)
	virtual void AIAction3() PURE_VIRTUAL(IAIActionInterface::AIActionC, return;)
	virtual void AIAction4() PURE_VIRTUAL(IAIActionInterface::AIActionD, return;)
	virtual void AIAddTarget(ACCharacter* Target, ACBaseTrigger* Trigger) PURE_VIRTUAL(IAIActionInterface::AIAddTarget, return;)
};
//타겟 정보 가져올 함수.. spawner, Target 등록. 사망시 spawner의 카운트 감소. 0이 되면 IsAlreadySpawned false로