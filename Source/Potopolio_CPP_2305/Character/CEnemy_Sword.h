// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CHumanoidEnemy.h"
#include "CEnemy_Sword.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class POTOPOLIO_CPP_2305_API ACEnemy_Sword : public ACHumanoidEnemy
{
	GENERATED_BODY()
	
public:
	ACEnemy_Sword();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;

};
