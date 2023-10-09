// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/CTrigger_Parkour.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Logger.h"

ACTrigger_Parkour::ACTrigger_Parkour()
{
	SystemText = "Press Space to Parkour";
	Obstacle = CreateDefaultSubobject<UStaticMeshComponent>("ObstacleMesh");
	SetRootComponent(Obstacle);
}

void ACTrigger_Parkour::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void ACTrigger_Parkour::BeginPlay()
{
	Super::BeginPlay();
}

const bool ACTrigger_Parkour::TriggableDegree(const FVector& ActorForwardVector)
{

	float degree = FVector::DotProduct(GetActorForwardVector(), ActorForwardVector);

	if ( abs(degree) < 0.5f)
		return true;
	else
		return false;

}

void ACTrigger_Parkour::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
