// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CNotify_SetArrowCondition.generated.h"

UCLASS()
class POTOPOLIO_CPP_2305_API UCNotify_SetArrowCondition : public UAnimNotify
{
	GENERATED_BODY()

protected:
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	UPROPERTY(EditAnywhere)
		bool VisibleArrowModel = false;

	UPROPERTY(EditAnywhere)
		bool SetNewElement = false;
};
