// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Weapon/CBow.h"
#include "CNotify_SetBowState.generated.h"


UCLASS()
class POTOPOLIO_CPP_2305_API UCNotify_SetBowState : public UAnimNotify
{
	GENERATED_BODY()

protected:
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		EBowState BowState;
};
