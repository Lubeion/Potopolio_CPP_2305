// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/CBaseTrigger.h"
#include "CTrigger_Spawner.generated.h"

/**
 * 
 */
UCLASS()
class POTOPOLIO_CPP_2305_API ACTrigger_Spawner : public ACBaseTrigger
{
	GENERATED_BODY()
	
protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void TriggerF(ACCharacter* Character) override { StartSpawn(Character); }

	UFUNCTION()
		void TColBeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void TColEndOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void ConnectedDeadEvent() override;

public:
	ACTrigger_Spawner();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetSpawnerActive() { IsAlreadySpawned = false; }

private:
	void StartSpawn(ACCharacter* Character);

protected:
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class ACCharacter>> SpawnerEnemyTypes;

	bool IsAlreadySpawned = false;
	bool IsOverlapped = false;

	UPROPERTY(EditAnywhere)
		int SpawnCount = 0;
	UPROPERTY(EditAnywhere)
		int SpawnRadius = 64;

	UPROPERTY(EditDefaultsOnly)
		class USphereComponent* TextCollider;
	UPROPERTY(EditDefaultsOnly)
		class USphereComponent* SpawnRadiusPreview;

	int curCount = 0;

	// 소환 할 ACCharacter 넣고 Activate 시 Spawn, 일정 제한에 도달하면 다시 False, 소환된 객체 수 체크
	// 체크 된 수가 0이 되면 다시 Actiavte 가능.

	//ACCharacter에 Owning Trigger 만들고, Spawner에서 등록. 사망시 Trigger가 존재하면 SpawnedEnemies에서 find, delete
};
