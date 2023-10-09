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

	// ��ȯ �� ACCharacter �ְ� Activate �� Spawn, ���� ���ѿ� �����ϸ� �ٽ� False, ��ȯ�� ��ü �� üũ
	// üũ �� ���� 0�� �Ǹ� �ٽ� Actiavte ����.

	//ACCharacter�� Owning Trigger �����, Spawner���� ���. ����� Trigger�� �����ϸ� SpawnedEnemies���� find, delete
};
