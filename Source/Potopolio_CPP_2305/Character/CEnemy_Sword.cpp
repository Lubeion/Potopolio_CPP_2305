// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CEnemy_Sword.h"

ACEnemy_Sword::ACEnemy_Sword()
{
}

void ACEnemy_Sword::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	MaxShieldCount = 3;
	MaxHp = 200;
	Exp = 10;

}

void ACEnemy_Sword::BeginPlay()
{
	Super::BeginPlay();
}

void ACEnemy_Sword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
