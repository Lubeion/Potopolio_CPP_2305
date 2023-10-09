// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SwordInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USwordInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class POTOPOLIO_CPP_2305_API ISwordInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void BeginComboAttack() PURE_VIRTUAL(ISwordInterface::BeginComboAttack, return;)
	virtual void EndComboAttack() PURE_VIRTUAL(ISwordInterface::BeginComboAttack, return;)
	virtual void BeginPowerAttack() PURE_VIRTUAL(ISwordInterface::BeginComboAttack, return;)
	virtual void EndPowerAttack() PURE_VIRTUAL(ISwordInterface::BeginComboAttack, return;)
	virtual void NextComboAttack() PURE_VIRTUAL(ISwordInterface::BeginNextComboAttack, return;)
	virtual void EndComboMontage(UAnimMontage * AttackMontage, bool Interrupted) PURE_VIRTUAL(ISwordInterface::EndComboMontage, return;)
	virtual bool GetNextComboEnabled() PURE_VIRTUAL(ISwordInterface::GetNextComboEnabled, return false;)
	virtual void ActivateAttack(bool Activate) PURE_VIRTUAL(ISwordInterface::ActivateAttack, return;)

};
