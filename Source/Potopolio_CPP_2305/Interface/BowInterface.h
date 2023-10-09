// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CEnums.h"
#include "Projectile/CProjectileArrow.h"
#include "BowInterface.generated.h"

enum class EBowState : uint8;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBowInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class POTOPOLIO_CPP_2305_API IBowInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void BeginDraw() PURE_VIRTUAL(IBowInterface::BeginDraw, return;)
	virtual void EndDraw() PURE_VIRTUAL(IBowInterface::EndDraw, return;)
	virtual void BeginZoom() PURE_VIRTUAL(IBowInterface::BeginZoom, return;)
	virtual void EndZoom() PURE_VIRTUAL(IBowInterface::EndZoom, return;)
	virtual const ACProjectileArrow* GetArrow() PURE_VIRTUAL(IBowInterface::GetArrow, return nullptr;)
	virtual const EBowState GetBowState() PURE_VIRTUAL(IBowInterface::GetBowState, return EBowState::Idle;)
	virtual void SetBowState(EBowState BowStateIn) PURE_VIRTUAL(IBowInterface::SetBowState, return;)
	virtual void OrderPlayAnimMontage(EBowState BowStateIn) PURE_VIRTUAL(IBowInterface::OrderPlayAnimMontage, return;)
	virtual	ACProjectileArrow* GetArrowModel() PURE_VIRTUAL(IBowInterface::GetArrowModel, return nullptr;)
	virtual FActorSpawnParameters GetArrowSpawnParameters() PURE_VIRTUAL(IBowInterface::GetArrowSpawnParameters, return FActorSpawnParameters::FActorSpawnParameters();)
	virtual FVector GetArrowVelocity() PURE_VIRTUAL(IBowInterface::GetArrowVelocity, return FVector();)
	virtual FVector InterfaceGetActorLocation() PURE_VIRTUAL(IBowInterface::InterfaceGetActorLocation, return FVector();)

};
