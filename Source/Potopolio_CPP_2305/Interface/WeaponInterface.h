// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ElementsFunctionLibrary.h"
#include "WeaponInterface.generated.h"

enum class EWeaponType : uint8;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UWeaponInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class POTOPOLIO_CPP_2305_API IWeaponInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void BeginBasicAction() PURE_VIRTUAL(IWeaponInterface::BeginBasicAction, return;)
	virtual void EndBasicAction() PURE_VIRTUAL(IWeaponInterface::EndBasicAction, return;)
	virtual void BeginIntensiveAction() PURE_VIRTUAL(IWeaponInterface::BeginIntensiveAction, return;)
	virtual void EndIntensiveAction() PURE_VIRTUAL(IWeaponInterface::EndIntensiveAction, return;)

	virtual void BeginElementAction() PURE_VIRTUAL(IWeaponInterface::BeginElementAction, return;)
	virtual bool EndElementAction(const FVector2D & MousePos) PURE_VIRTUAL(IWeaponInterface::EndElementAction, return true;)

	virtual bool EquipWeapon() PURE_VIRTUAL(IWeaponInterface::EquipWeapon, return false;)
	virtual bool UnequipWeapon() PURE_VIRTUAL(IWeaponInterface::UnequipWeapon, return false;)
	virtual void EndUnequipWeaponEvent() PURE_VIRTUAL(IWeaponInterface::EndUnequipWeaponEvent, return;)

	virtual void SetDamage(float InDamage) PURE_VIRTUAL(IWeaponInterface::SetDamage, return;)
	virtual void SetVisiblity(bool IsVisible) PURE_VIRTUAL(IWeaponInterface::SetVisiblity, return;)
	virtual void SetNewElementVisuality() PURE_VIRTUAL(IWeaponInterface::SetNewElementVisuality, return;)

	virtual const FName GetSocketName() PURE_VIRTUAL(IWeaponInterface::GetSocketName, return L"None";)
	virtual const FName GetSocketName_UnGrapped() PURE_VIRTUAL(IWeaponInterface::GetSocketName_UnGrapped, return L"None";)
	virtual const EWeaponType GetWeaponType() PURE_VIRTUAL(IWeaponInterface::GetWeaponType, return EWeaponType::None;)
	virtual const EElements GetElementType() PURE_VIRTUAL(IWeaponInterface::GetElementType, return EElements::None;)
	virtual void  SetElementType(EElements InElementType) PURE_VIRTUAL(IWeaponInterface::SetElementType, return;)
	virtual const USkeletalMeshComponent* GetSKMesh() PURE_VIRTUAL(IWeaponInterface::GetSKMesh, return nullptr;)
};

