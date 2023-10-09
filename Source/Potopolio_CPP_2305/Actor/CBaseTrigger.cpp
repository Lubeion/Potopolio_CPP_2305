// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/CBaseTrigger.h"
#include "Interface/PlayerActionInterface.h"
#include "Components/SphereComponent.h"
#include "Logger.h"

// Sets default values
ACBaseTrigger::ACBaseTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ACBaseTrigger::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

// Called when the game starts or when spawned
void ACBaseTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACBaseTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACBaseTrigger::ColliderOverlapTrigger(bool IsBegin, AActor* OtherActor)
{
	if (IsBegin)
	{
		if (auto* Player = Cast<IPlayerActionInterface>(OtherActor))
		{
			Player->UISystemText(SystemText);
			Player->SetTrigger(true, this);
		}
	}
	else
	{
		if (auto* Player = Cast<IPlayerActionInterface>(OtherActor))
		{
			Player->UISystemText("", false);
			Player->SetTrigger(false, this);
		}
	}
}


