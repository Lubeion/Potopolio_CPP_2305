// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/CBowAnimInstance.h"
#include "Logger.h"

void UCBowAnimInstance::NativeUpdateAnimation(float const DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (auto* BOwner = Cast<ACBow>(GetOwningActor()))
	{
		CurBowState = Cast<IBowInterface>(BOwner)->GetBowState();
	}

}