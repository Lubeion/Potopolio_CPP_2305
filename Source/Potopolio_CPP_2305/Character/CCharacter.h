// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/CommonActionInterface.h"
#include "ElementsFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Projectile/CProjectileMagicArrow.h"
#include "Projectile/CProjectileMagicStorm.h"
#include "CCharacter.generated.h"

#define ShieldBrokenBonus 2.0f

enum class EElements : uint8;
enum class SimpleState : uint8;
enum class BattleState : uint8;

UCLASS(Abstract)
class POTOPOLIO_CPP_2305_API ACCharacter 
	: public ACharacter
	, public ICommonActionInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform)override;

	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	//void ReceiveAnyDamage(float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetSimpleState(const ESimpleState& InSState) { this->SState = InSState; }
	const ESimpleState& GetSimpleState() { return SState; }

	void SetBattleState(const EBattleState& InBState) { this->BState = InBState; }
	const EBattleState& GetBattleState() { return BState; }

	void SetSimpleStateIdle() { SState = ESimpleState::Idle; }
	void SetSimpleStateBattle();

	bool CheckAnimMontagePlayable();
	bool CheckActionPlayable();

	void SetAnimMontagePlayable(bool CanPlay);
	void SetActionPlayable(bool CanPlay);

	const FTransform GetActorSpawnTransform();

	virtual void Damaged(const EElements& InElementType, const float& Damage);
	const int& GetShieldCount() { return ShieldCount; }
	UStaticMeshComponent* GetShieldMesh() { return ShieldMesh; }

protected:
	virtual void HitUpdateFunction() {};

public:

protected:
	UPROPERTY(BlueprintReadOnly)
		float MaxHp;
	UPROPERTY(BlueprintReadOnly)
		float Hp;
	UPROPERTY(BlueprintReadOnly)
		float MaxMp;
	UPROPERTY(BlueprintReadOnly)
		float Mp;
	UPROPERTY(BlueprintReadOnly)
		float MaxExp;
	UPROPERTY(BlueprintReadOnly)
		float Exp;
	UPROPERTY(BlueprintReadOnly)
		int Level = 1;
	UPROPERTY(BlueprintReadOnly)
		int MaxShieldCount;
	UPROPERTY(BlueprintReadOnly)
		int ShieldCount;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class ACProjectileMagicArrow> MagicArrowClass;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class ACProjectileMagicStorm> MagicStormClass;

	UPROPERTY(EditDefaultsOnly)
		class UStaticMeshComponent* ShieldMesh;
	UPROPERTY(VisibleDefaultsOnly)
		class USphereComponent* ShieldCollider;

	UPROPERTY(EditDefaultsOnly)
		EElements ElementType;

	UPROPERTY(EditDefaultsOnly)
		class UDataTable* ElementShieldData;
	UPROPERTY(EditDefaultsOnly)
		ESimpleState SState;
	UPROPERTY(EditDefaultsOnly)
		EBattleState BState;

	bool bCanAction = true;
	bool bCanPlayAnimMontage = true;

	const float BattleModeEndDelay = 3.0f;
	FTimerHandle T1Handle;
	FTimerHandle T2Handle;

	UPROPERTY(BlueprintReadOnly)
		FVector SpawnActorLocation;

	float BaseDamage;
private:
	
};
