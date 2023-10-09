// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/CTrigger_MapLoader.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Character/CPlayer.h"
#include "Logger.h"

ACTrigger_MapLoader::ACTrigger_MapLoader()
{
	SystemText = "Press F to Activate";
	TextCollider = CreateDefaultSubobject<USphereComponent>("TCol");
}

void ACTrigger_MapLoader::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

}

void ACTrigger_MapLoader::BeginPlay()
{
	Super::BeginPlay();
	
	TextCollider->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::TColBeginOverlapEvent);
	TextCollider->OnComponentEndOverlap.AddDynamic(this, &ThisClass::TColEndOverlapEvent);;
}

void ACTrigger_MapLoader::TColBeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ColliderOverlapTrigger(true, OtherActor);
	//if (auto* Player = Cast<IPlayerActionInterface>(OtherActor))
	//{
	//	Player->UISystemText(SystemText);
	//	//player�� Trigger ����ϰ�, �����ϰ�.. F ������ TriggerF �Լ� ����.
	//	//�̰� OtherActor �� �޴� �Լ��� ���� BaseTrigger�� �����ΰ� ������ �ֱ�. (����κ�)
	//}
}

void ACTrigger_MapLoader::TColEndOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ColliderOverlapTrigger(false, OtherActor);
	/*if (auto* Player = Cast<IPlayerActionInterface>(OtherActor))
	{
		Player->UISystemText("", false);
	}*/
}

void ACTrigger_MapLoader::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACTrigger_MapLoader::LoadWorldLevel()
{
	if (!Available)
		return;

	if (!WorldToLoad)
		Logger::Print(FString("NoWorldLevelExist"));
	
	UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), WorldToLoad);

}
