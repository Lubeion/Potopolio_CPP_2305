// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Weapon/CWeapon.h"
#include "Character/CHumanoidCharacter.h"
#include "CHumanoidAnimInstanceIK.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class POTOPOLIO_CPP_2305_API UCHumanoidAnimInstanceIK : public UAnimInstance
{
	GENERATED_BODY()
public:
	void NativeUpdateAnimation(float const DeltaSeconds) override;

private:
	void TraceForIK(FName const Bone, float& Distance, FRotator& Rotator);

private:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
		EWeaponType WeaponType;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		float Speed;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		float Direction;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		float Pitch;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		float DashDirection;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		FVector TranslationP;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		FVector TranslationL;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		FVector TranslationR;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		FRotator RotationL;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		FRotator RotationR;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		FName IKBoneL;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		FName IKBoneR;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		ESimpleState SState = ESimpleState::Idle;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		EBattleState BState = EBattleState::Idle;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		bool IsVelocityForward;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		EBowState CurBowState = EBowState::Idle;

	static int32 const TraceDistance = 50;
	static int32 const InterpSpeed = 50;
	float InputDirection = 0.0f;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		float BowAimVertical;
};
