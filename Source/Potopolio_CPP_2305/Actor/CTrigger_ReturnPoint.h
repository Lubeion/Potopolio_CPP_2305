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
	//Player���� �ش� Ʈ������ ��ġ���� ����. �ƴϸ� ����(�⺻ ��������Ʈ) ��Ȱ�ϵ���.
	//Ȱ��ȭ�� ����Ʈ�� �ð������� ǥ��. ���ÿ� �ٸ� Ʈ���� �������� Ž���Ͽ� ǥ�� ����.
};
