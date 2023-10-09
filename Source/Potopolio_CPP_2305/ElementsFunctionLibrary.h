// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "Math/Vector2D.h"
#include "Engine/DataTable.h"
#include "CEnums.h"
#include "GameFramework/DamageType.h"
#include "ElementsFunctionLibrary.generated.h"

/**
 * 
 */
#define ElementDamageBonus 1.8
#define ElementDamagePenalty 0.6


enum class EElements : uint8;

UCLASS()
class UElementDamageTypeNone : public UDamageType
{
	GENERATED_BODY()
};

UCLASS()
class UElementDamageTypeFire : public UDamageType
{
	GENERATED_BODY()
};

UCLASS()
class UElementDamageTypeIce : public UDamageType
{
	GENERATED_BODY()
};

UCLASS()
class UElementDamageTypeEletric : public UDamageType
{
	GENERATED_BODY()
};


USTRUCT(BlueprintType)
struct FElementMaterialInstanceData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)	EElements Element;
	UPROPERTY(EditAnywhere)	class UMaterialInstance* MaterialInstance;

};

USTRUCT(BlueprintType)
struct FElementParticleData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)	EElements Element;
	UPROPERTY(EditAnywhere)	class UParticleSystem* ParticleSystem;

};

UCLASS()
class POTOPOLIO_CPP_2305_API UElementsFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
		static void SetMaterialInstance(const UDataTable* Data, const EElements& OtherElement, UStaticMeshComponent* Mesh);
	UFUNCTION(BlueprintCallable)
		static void SetParticle(const UDataTable* Data, const EElements& OtherElement, UParticleSystemComponent* Particle);
	UFUNCTION(BlueprintCallable)
		static UParticleSystem* GetParticleSystem(const UDataTable* Data, const EElements& OtherElement);
	UFUNCTION(BlueprintCallable) 
		static bool SelectElement(EElements& SelfElement, const FVector2D& MousePos);

	static void ResetElementData() { PreElementData = EElements::None; }
private:
	static float MinSelectDist;
	static EElements PreElementData;
};
