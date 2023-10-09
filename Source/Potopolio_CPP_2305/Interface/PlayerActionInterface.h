// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerActionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPlayerActionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class POTOPOLIO_CPP_2305_API IPlayerActionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void BeginActionReturn()			/*B*/						PURE_VIRTUAL(IPlayerActionInterface::BeginActionReturn, return;)
	virtual void EndActionReturn()											PURE_VIRTUAL(IPlayerActionInterface::EndActionReturn, return;)
	virtual void BeginActionTargeting()			/*Q*/						PURE_VIRTUAL(IPlayerActionInterface::BeginActionTargeting, return;)
	virtual void EndActionTargeting()										PURE_VIRTUAL(IPlayerActionInterface::EndActionTargeting, return;)
	virtual void BeginActionWeaponChange()		/*E*/						PURE_VIRTUAL(IPlayerActionInterface::BeginActionWeaponChange, return;)
	virtual void EndActionWeaponChange()									PURE_VIRTUAL(IPlayerActionInterface::EndActionWeaponChange, return;)
	virtual void BeginActionPotion()			/*R*/						PURE_VIRTUAL(IPlayerActionInterface::BeginActionPotion, return;)
	virtual void EndActionPotion()		 									PURE_VIRTUAL(IPlayerActionInterface::EndActionPotion, return;)
	virtual void BeginActionParkour()			/*Space*/					PURE_VIRTUAL(IPlayerActionInterface::BeginActionParkour, return;)
	virtual void EndActionParkour()		 									PURE_VIRTUAL(IPlayerActionInterface::EndActionParkour, return;)
	virtual void BeginActionWalk()				/*LShift*/					PURE_VIRTUAL(IPlayerActionInterface::BeginActionWalk, return;)
	virtual void EndActionWalk()		 									PURE_VIRTUAL(IPlayerActionInterface::EndActionWalk, return;)
	virtual void ZoomIn()						/*LButton*/					PURE_VIRTUAL(IPlayerActionInterface::ZoomIn, return;)
	virtual void ZoomOut()		 											PURE_VIRTUAL(IPlayerActionInterface::ZoomOut, return;)
	virtual void BeginInteractTrigger()			/*F*/						PURE_VIRTUAL(IPlayerActionInterface::BeginInteractTrigger, return;)
	virtual void EndInteractTrigger()		 								PURE_VIRTUAL(IPlayerActionInterface::EndInteractTrigger, return;)
	virtual void SetInputDirection(const FVector2D Direction)				PURE_VIRTUAL(IPlayerActionInterface::SetInputDirection, return;)
	virtual void UISystemText(const FString InText, bool isVisible = true)	PURE_VIRTUAL(IPlayerActionInterface::UISystemText, return;)
	virtual void SetTrigger(bool IsSetting, ACBaseTrigger* AddedTrigger)	PURE_VIRTUAL(IPlayerActionInterface::SetTrigger, return;)

};
