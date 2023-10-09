// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Character/CCharacter.h"
#include "CBaseTrigger.generated.h"

UCLASS(Abstract)
class POTOPOLIO_CPP_2305_API ACBaseTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACBaseTrigger();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ColliderOverlapTrigger(bool IsBegin, AActor* OtherActor);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	const FString& GetSystemText() { return SystemText; }

	virtual const bool TriggableDegree(const FVector& ActorForwardVector) { return true; }
	virtual const bool CheckAvailable() { return Available; }
	virtual void SetAvailable(bool WillAvailable) { Available = WillAvailable; }
	virtual void TriggerF(ACCharacter* Character) {};
	
	virtual void ConnectedDeadEvent() {};

protected:
	UPROPERTY(EditDefaultsOnly)
		class UParticleSystemComponent* Effect;
	UPROPERTY(EditAnywhere)
		FString SystemText = L"TestText";

	bool Available = true;

};
