// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Character/CCharacter.h"
#include "Interface/WeaponInterface.h"
#include "MontageFunctionLibrary.h"
#include "ElementsFunctionLibrary.h"
#include "CEnums.h"
#include "Logger.h"
#include "CWeapon.generated.h"

enum class EElements : uint8;

UCLASS(Abstract)
class POTOPOLIO_CPP_2305_API ACWeapon 
	: public AActor
	, public IWeaponInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void BeginPlay() override;

	virtual void SetNewElementVisuality() override;

	void SetVisiblity(bool IsVisible) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	const FName GetSocketName() override { return SocketName; }
	const FName GetSocketName_UnGrapped() override { return SocketName_UnGrapped; }

protected:
	UPROPERTY(BlueprintReadOnly)
		EWeaponType WeaponType;

	UPROPERTY(EditDefaultsOnly)
		class USkeletalMeshComponent* SK_WeaponMesh;
	UPROPERTY(EditDefaultsOnly)
		class UStaticMeshComponent* WeaponMesh;
	UPROPERTY(EditDefaultsOnly)
		class UDataTable* ElementWeaponData;

	UPROPERTY(EditDefaultsOnly)
		class UParticleSystemComponent* ElementEffect;
	UPROPERTY(EditDefaultsOnly)
		class UDataTable* ElementParticleData;

	UPROPERTY(EditDefaultsOnly)
		class USkeletalMeshComponent* SK_WeaponMesh_UnGrapped;
	UPROPERTY(EditDefaultsOnly)
		class UStaticMeshComponent* WeaponMesh_UnGrapped;

	UPROPERTY(EditDefaultsOnly)
		EElements ElementType;

	UPROPERTY(EditDefaultsOnly)
		class UDataTable* MontageData;
	UPROPERTY(EditDefaultsOnly)
		class UDataTable* SK_WeaponMontageData;

	UPROPERTY(EditDefaultsOnly)
		float Damage;

	UPROPERTY(EditDefaultsOnly)
		FName SocketName;
	UPROPERTY(EditDefaultsOnly)
		FName SocketName_UnGrapped;

private:
	const EWeaponType GetWeaponType() override { return WeaponType; }
	const EElements GetElementType() override { return ElementType; }
	const USkeletalMeshComponent* GetSKMesh() override { return SK_WeaponMesh; }
	void SetElementType(EElements InElementType) override { ElementType = InElementType; }
	bool EquipWeapon() override;
	bool UnequipWeapon() override;
	void EndUnequipWeaponEvent() override;
	void SetDamage(float InDamage) override { Damage = InDamage; }

protected:
	
	UFUNCTION()
		void EndEquipMontage(UAnimMontage* AttackMontage, bool Interrupted);
	UFUNCTION()
		void EndUnequipMontage(UAnimMontage* AttackMontage, bool Interrupted);
	UFUNCTION()
		void CallEquipMontage(UAnimMontage* AttackMontage, bool Interrupted);
};
