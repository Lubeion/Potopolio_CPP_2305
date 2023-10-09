// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CNotify_EndDash.generated.h"

/**
 * 
 */
UCLASS()
class POTOPOLIO_CPP_2305_API UCNotify_EndDash : public UAnimNotify
{
	GENERATED_BODY()

protected:
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
