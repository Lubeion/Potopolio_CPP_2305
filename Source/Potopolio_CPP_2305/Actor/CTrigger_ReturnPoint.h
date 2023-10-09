// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/CBaseTrigger.h"
#include "CTrigger_ReturnPoint.generated.h"

/**
 * 
 */
UCLASS()
class POTOPOLIO_CPP_2305_API ACTrigger_ReturnPoint : public ACBaseTrigger
{
	GENERATED_BODY()
	
protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//Player에서 해당 트리거의 위치정보 저장. 아니면 원점(기본 스폰포인트) 부활하도록.
	//활성화된 포인트는 시각적으로 표시. 동시에 다른 트리거 레벨에서 탐색하여 표시 해제.
};
