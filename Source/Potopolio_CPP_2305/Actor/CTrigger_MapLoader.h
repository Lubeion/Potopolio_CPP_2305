// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/CBaseTrigger.h"
#include "CTrigger_MapLoader.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class POTOPOLIO_CPP_2305_API ACTrigger_MapLoader : public ACBaseTrigger
{
	GENERATED_BODY()

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void TriggerF(ACCharacter* Character) override { LoadWorldLevel(); }

	UFUNCTION()
		void TColBeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void TColEndOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
public:
	ACTrigger_MapLoader();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//�ҷ��� MapLevel ����. ���۽� �ش� ���� �ҷ����� �⺻ ������������ �÷��̾� �̵� �� ȸ��.

	void LoadWorldLevel();

protected:
	UPROPERTY(EditAnywhere)
		class UWorld* WorldToLoad;

	UPROPERTY(EditDefaultsOnly)
		class USphereComponent* TextCollider;

};
