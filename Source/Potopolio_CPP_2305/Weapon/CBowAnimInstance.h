// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Weapon/CBow.h"
#include "CBowAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class POTOPOLIO_CPP_2305_API UCBowAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	void NativeUpdateAnimation(float const DeltaSeconds) override;

private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		EBowState CurBowState = EBowState::Idle;
};
