// Fill out your copyright notice in the Description page of Project Settings.

#include "Actor/CTrigger_Spawner.h"
#include "Components/SphereComponent.h"
#include "Interface/AIActionInterface.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Particles/ParticleSystemComponent.h"
#include "Logger.h"

ACTrigger_Spawner::ACTrigger_Spawner()
{
	SystemText = "Press F to Activate";

	TextCollider = CreateDefaultSubobject<USphereComponent>("TCol");
	SpawnRadiusPreview = CreateDefaultSubobject<USphereComponent>("PreView");
	SpawnRadiusPreview->SetupAttachment(TextCollider);

	Effect = CreateDefaultSubobject<UParticleSystemComponent>("Effect");
	Effect->SetupAttachment(RootComponent);
}

void ACTrigger_Spawner::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	SpawnRadiusPreview->SetSphereRadius(SpawnRadius);
}

void ACTrigger_Spawner::BeginPlay()
{
	Super::BeginPlay();

	TextCollider->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::TColBeginOverlapEvent);
	TextCollider->OnComponentEndOverlap.AddDynamic(this, &ThisClass::TColEndOverlapEvent);
}

void ACTrigger_Spawner::TColBeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsAlreadySpawned)
	{
		ColliderOverlapTrigger(true, OtherActor);
		IsOverlapped = true;
	}

}

void ACTrigger_Spawner::TColEndOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(IsOverlapped)
		ColliderOverlapTrigger(false, OtherActor);
}

void ACTrigger_Spawner::ConnectedDeadEvent()
{
	curCount--;
	if (curCount > 0)
		return;
	curCount = 0;
	IsAlreadySpawned = false;
}

void ACTrigger_Spawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACTrigger_Spawner::StartSpawn(ACCharacter* Character)
{
	if (IsAlreadySpawned)
		return;

	if (SpawnerEnemyTypes.Num() <= 0)
	{
		Logger::Print(FString("NoEnemyExist"));
		return;
	}

	for (int i = 0; i < SpawnCount; i++)
	{
		FVector RandomPos = GetActorLocation();
		int Num = FMath::RandRange(-SpawnRadius, SpawnRadius);

		RandomPos.X += Num;
		RandomPos.Y += sqrt(pow(SpawnRadius, 2) - pow(Num, 2));

		FVector LandFinder = RandomPos - FVector(0, 0, 100);
		FHitResult Result;
		UKismetSystemLibrary::LineTraceSingle(GetWorld(), RandomPos, LandFinder,
			ETraceTypeQuery::TraceTypeQuery1, true, {}, EDrawDebugTrace::Type::None, Result, true);

		if (auto* SpawnedEnemy = GetWorld()->SpawnActor(SpawnerEnemyTypes[SpawnCount].Get(), &Result.Location))
		{
			if (auto* Enemy = Cast<ACCharacter>(SpawnedEnemy))
			{
				curCount++;
				if (auto* IEnemy = Cast<IAIActionInterface>(Enemy))
				{
					IEnemy->AIAddTarget(Character, this);
				}
				
			}
		}
	}
	IsAlreadySpawned = true;
}
