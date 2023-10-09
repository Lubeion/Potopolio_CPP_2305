// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CHumanoidEnemy.h"
#include "Perception/AIPerceptionComponent.h"
#include "Character/CPlayer.h"
#include "Perception/AISenseConfig_Sight.h"
#include "AIController.h"
#include "Logger.h"
#include "CEnemyWidget.h"
#include "Components/WidgetComponent.h"

ACHumanoidEnemy::ACHumanoidEnemy()
{
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>("AIPerception");

	SightSense = CreateDefaultSubobject<UAISenseConfig_Sight>("SightSense");

	SightSense->SightRadius = 500.0f;
	SightSense->LoseSightRadius = 550.0f;
	SightSense->PeripheralVisionAngleDegrees = 75.0f;
	SightSense->DetectionByAffiliation.bDetectEnemies = true;
	SightSense->DetectionByAffiliation.bDetectFriendlies = true;
	SightSense->DetectionByAffiliation.bDetectNeutrals = true;

	AIPerception->ConfigureSense(*SightSense);
	AIPerception->SetDominantSense(SightSense->GetSenseImplementation());

	Widget = CreateDefaultSubobject<UWidgetComponent>("Widget");
	Widget->SetupAttachment(RootComponent);
	Widget->SetWidgetSpace(EWidgetSpace::Screen);
	
	OnDestroyed.AddDynamic(this, &ACHumanoidEnemy::DestroyedEvent);
}

void ACHumanoidEnemy::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	AIPerception->OnPerceptionUpdated.AddUniqueDynamic(this, &ThisClass::OnPerceptionUpdated);
	
}

void ACHumanoidEnemy::BeginPlay()
{
	Super::BeginPlay();
	int Element = FMath::RandHelper64(3) + 1;
	ElementType = EElements(Element);

	UElementsFunctionLibrary::SetMaterialInstance(ElementShieldData, ElementType, ShieldMesh);

	ShieldCount = MaxShieldCount;
	Hp = MaxHp;

	if (UCEnemyWidget* EnemyWidget = Cast<UCEnemyWidget>(Widget->GetUserWidgetObject()))
	{
		EnemyWidget->SetLevel(Level);
		EnemyWidget->SetElementType(ElementType);
		EnemyWidget->UpdateHP(Hp, MaxHp);
		EnemyWidget->UpdateShield(ShieldCount, MaxShieldCount);
	}
}

void ACHumanoidEnemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (auto* AIController = Cast<AAIController>(GetController()))
	{
		AIController->RunBehaviorTree(AIBehaviorTree);
	}
}

void ACHumanoidEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ACHumanoidEnemy::OnPerceptionUpdated(const TArray<AActor*>& OutActors)
{
	if (Target == nullptr)
	{
		for (AActor* Actor : OutActors)
		{
			if (auto* Hostile = Cast<ACPlayer>(Actor))
			{
				Target = Hostile;
				return;
			}
		}
	}
}

void ACHumanoidEnemy::DestroyedEvent(AActor* DestroyedActor)
{
	DeadEventTrigger->ConnectedDeadEvent();
}

void ACHumanoidEnemy::HitUpdateFunction()
{
	if (UCEnemyWidget* EnemyWidget = Cast<UCEnemyWidget>(Widget->GetUserWidgetObject()))
	{
		EnemyWidget->UpdateHP(Hp, MaxHp);
		EnemyWidget->UpdateShield(ShieldCount, MaxShieldCount);
	}
}

void ACHumanoidEnemy::AIActionA()
{
	BeginActionA();
	EndActionA();
}

void ACHumanoidEnemy::AIActionB()
{
	BeginActionB();
	EndActionB();
}

void ACHumanoidEnemy::AIAction1()
{
	BeginAction1();
	EndAction1();
}

void ACHumanoidEnemy::AIAction2()
{
	BeginAction2();
	EndAction2();
}

void ACHumanoidEnemy::AIAction3()
{
	BeginAction3();
	EndAction3();
}

void ACHumanoidEnemy::AIAction4()
{
	BeginAction4();
	EndAction4();
}

void ACHumanoidEnemy::AIAddTarget(ACCharacter* Character, ACBaseTrigger* Trigger)
{
	if (auto* Player = Cast<ACPlayer>(Character))
	{
		Target = Player;
	}

	DeadEventTrigger = Trigger;
}
