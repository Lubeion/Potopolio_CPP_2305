// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Character/CParkourComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/PlayerController.h"
#include "Interface/BowInterface.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/TimelineComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Character/CBasicPlayerController.h"
#include "CPlayerUserWidget.h"
#include "Weapon/CBow.h"
#include "Kismet/GameplayStatics.h"
#include "Interface/BowInterface.h"
#include "Components/BoxComponent.h"

ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	ParkourComponent = CreateDefaultSubobject<UCParkourComponent>("Parkour");
	ZoomTimeline = CreateDefaultSubobject<UTimelineComponent>("ZoomTimeline");

	BlendTimeOnZoomIn = 0.125f;

	TriggerChecker = CreateDefaultSubobject<UBoxComponent>("TriggerChecker");
	TriggerChecker->SetupAttachment(RootComponent);

}

void ACPlayer::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	MaxHp = 100;
	MaxMp = 50;
	MaxExp = 100;
	BaseDamage = 10;

}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

	TriggerChecker->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::BeginTriggerChecker);
	TriggerChecker->OnComponentEndOverlap.AddDynamic(this, &ThisClass::EndTriggerChecker);

	TargetArmLength = SpringArm->TargetArmLength;
	SocketOffset = SpringArm->SocketOffset;
	FieldOfView = Camera->FieldOfView;

	if (BlendCurveOnZoomIn)
	{
		FOnTimelineFloat OnZoom;
		OnZoom.BindDynamic(this, &ThisClass::Zoom);
		ZoomTimeline->AddInterpFloat(BlendCurveOnZoomIn, OnZoom);
		ZoomTimeline->SetPlayRate(1 / BlendTimeOnZoomIn);
	}

	if (WidgetClass != nullptr)
	{
		Widget = CreateWidget(Cast<ACBasicPlayerController>(GetController()), WidgetClass, "Widget");
		Widget->AddToViewport();
	}

	LevelInit();
	
}

void ACPlayer::Landed(FHitResult const& HitResult)
{
	Super::Landed(HitResult);
	ParkourComponent->BeginParkour();

}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsNeedMousePos)
	{
		if (auto* const PlayerWidget = Cast<UCPlayerUserWidget>(Widget))
		{
			if (APlayerController* APController = Cast<APlayerController>(GetController()))
			{
				APController->GetMousePosition(MousePos.X, MousePos.Y);
			}
			PlayerWidget->SetMousePos(MousePos);
		}
	}

	if (CurBowState != EBowState::Idle)
	{
		BowAimVirtical = GetBaseAimRotation().Pitch;
	}
	else
		BowAimVirtical = 0;

	if (TraceArrowProjectile)
	{
		if (auto* const Bow = Cast<IBowInterface>(Weapon))
		{

			FPredictProjectilePathParams Params;
			Params.StartLocation = Bow->InterfaceGetActorLocation();
			Params.LaunchVelocity = Bow->GetArrowVelocity();
			Params.ActorsToIgnore = {this};
			Params.DrawDebugType = EDrawDebugTrace::ForOneFrame;
			Params.OverrideGravityZ = -980.0f;
			Params.ProjectileRadius = 5.0f;
			Params.MaxSimTime = 1.0f;
			Params.bTraceWithCollision = true;
			
			FPredictProjectilePathResult Result;
			UGameplayStatics::PredictProjectilePath(GetWorld(), Params, Result
			);
		}
	}

	static float SlowTimer = 0.1f;

	if (SlowTimer >= 0)
	{
		SlowTimer -= DeltaTime;
	}
	else
	{
		if (auto* Trigger = Cast<ACBaseTrigger>(RegisteredTrigger))
		{
			if (Trigger->TriggableDegree(GetActorForwardVector()))
			{
				RegisteredTrigger = Trigger;
				if (Widget)
				{
					UISystemText(Trigger->GetSystemText());
				}
			}
		}

		SlowTimer = 0.1f;
	}
}

void ACPlayer::GainEXP(const float& InExp)
{
	Exp += InExp;

	if (Exp >= MaxExp)
	{
		Exp -= MaxExp;

		Level++;
		LevelUP();
	}
}

void ACPlayer::BeginTriggerChecker(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == this || OtherActor->GetOwner() == this)
		return;

	if (auto* Trigger = Cast<ACBaseTrigger>(OtherActor))
	{
		RegisteredTrigger = Trigger;
		if (Trigger->TriggableDegree(GetActorForwardVector()))
		{
			if (Widget)
			{
				UISystemText(Trigger->GetSystemText());
			}
		}
	}
}

void ACPlayer::EndTriggerChecker(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (auto* Trigger = Cast<ACBaseTrigger>(OtherActor))
	{
		if (RegisteredTrigger == Trigger)
		{
			UISystemText(Trigger->GetSystemText(), false);
			RegisteredTrigger = nullptr;
		}
	}
}

void ACPlayer::BeginActionA()
{
	Super::BeginActionA();
	if (Weapon->GetWeaponType() == EWeaponType::Bow)
		TraceArrowProjectile = true;
}

void ACPlayer::EndActionA()
{
	Super::EndActionA();
	TraceArrowProjectile = false;
}

void ACPlayer::BeginAction1()
{
	if (Mp < Skill1Cost)
		return;

	Super::BeginAction1();
	StartMousePosRecord();

	Action1OrderedIn = true;

}

void ACPlayer::EndAction1()
{
	if (!Action1OrderedIn)
		return;

	EndMousePosRecord();
	if (UElementsFunctionLibrary::SelectElement(ElementType, MousePos))
	{
		if(CheckAnimMontagePlayable())
			if (ElementType != EElements::None)
			{
				Super::EndAction1();
				Mp -= Skill1Cost;
			}

		UpdateWidgetElementColor();
	}

	Action1OrderedIn = false;
	UpdateWidgetMP();

}

void ACPlayer::BeginAction2()
{
	if (Mp < Skill2Cost)
		return;
	Super::BeginAction2();

	FHitResult Results;

	UKismetSystemLibrary::LineTraceSingle(GetWorld(),
		Camera->GetComponentLocation(),
		Camera->GetComponentLocation() + Camera->GetForwardVector() * 300,
		ETraceTypeQuery::TraceTypeQuery1,
		false,
		{ this },
		EDrawDebugTrace::Type::None,
		Results,
		true
	);

	if (Results.bBlockingHit)
	{
		SpawnActorLocation = Results.Location;
	}
	else
	{
		UKismetSystemLibrary::LineTraceSingle(GetWorld(),
			Camera->GetComponentLocation() + Camera->GetForwardVector() * 600,
			Camera->GetComponentLocation() + Camera->GetForwardVector() * 600 + FVector(0, 0, -600),
			ETraceTypeQuery::TraceTypeQuery1,
			false,
			{ this },
			EDrawDebugTrace::Type::None,
			Results,
			true
		);

		if (Results.bBlockingHit)
		{
			SpawnActorLocation = Results.Location;
		}
		else
		{
			Action2OrderedIn = false;
			return;
		}
	}

	StartMousePosRecord();
	Action2OrderedIn = true;

}

void ACPlayer::EndAction2()
{
	if (!Action2OrderedIn)
		return;

	EndMousePosRecord();
	if (UElementsFunctionLibrary::SelectElement(ElementType, MousePos))
	{
		if (CheckAnimMontagePlayable())
			if (ElementType != EElements::None)
			{
				Super::EndAction2();
				Mp -= Skill2Cost;
			}

		UpdateWidgetElementColor();
	}
	Action2OrderedIn = false;

	UpdateWidgetMP();
}

void ACPlayer::BeginAction3()
{
	if (Mp < Skill3Cost)
		return;

	if (!Weapon)
		return;
	StartMousePosRecord();
	
	Weapon->BeginElementAction();

	Action3OrderedIn = true;

}

void ACPlayer::EndAction3()
{
	if (!Action3OrderedIn)
		return;

	if (!Weapon)
		return;

	EndMousePosRecord();

	if (CheckAnimMontagePlayable())
		if (Weapon->EndElementAction(MousePos))
			Mp -= Skill3Cost;

	ElementType = Weapon->GetElementType();

	UpdateWidgetElementColor();
	Action3OrderedIn = false;
	UpdateWidgetMP();

}

void ACPlayer::BeginAction4()
{
}

void ACPlayer::EndAction4()
{
	UpdateWidgetHP();
	UpdateWidgetMP();

}
//void (UAnimMontage* MontageToPlay, bool Interuppted); 
//GetMesh()->GetAnimInstnace()->OnMontageEnded.AddDynamic() <- 공용이니 마지막에  removeDynamic
void ACPlayer::BeginActionReturn()
{
}

void ACPlayer::EndActionReturn()
{
}

void ACPlayer::BeginActionTargeting()
{
}

void ACPlayer::EndActionTargeting()
{
}

void ACPlayer::BeginActionWeaponChange()
{
	if (Weapon->UnequipWeapon())
	{
		PreWeapon = Weapon;

		if (MaxWeaponIndex > CurWeaponIndex)
		{
			CurWeaponIndex++;
			Weapon = Weapons[CurWeaponIndex];
		}
		else if(MaxWeaponIndex == CurWeaponIndex)
		{
			CurWeaponIndex = 0;
			Weapon = Weapons[CurWeaponIndex];
		}

		if (auto PWidget = Cast<UCPlayerUserWidget>(Widget))
		{
			PWidget->SetCurWeaponType(Weapon->GetWeaponType());
		}

		Weapon->EndUnequipWeaponEvent();
	}
}

void ACPlayer::EndActionWeaponChange()
{
}

void ACPlayer::BeginActionPotion()
{
	if (Mp < MaxMp)
	{
		Mp += 30;

		if (Mp > MaxMp)
			Mp = MaxMp;
	}
	UpdateWidgetMP();
}

void ACPlayer::EndActionPotion()
{
}

void ACPlayer::BeginActionParkour()
{
	if (!GetCharacterMovement()->IsFalling())
		if (!ParkourComponent->BeginParkour())
		{
			WillDash = true;
		}
}

void ACPlayer::EndActionParkour()
{
	if (!WillDash || SState == ESimpleState::Dead || BState != EBattleState::Idle)
		return;

	WillDash = false;

	if (CheckAnimMontagePlayable())
	{
		BState = EBattleState::Dash;
		SetAnimMontagePlayable(false);
		if (Weapon->GetWeaponType() == EWeaponType::Bow)
			Cast<IBowInterface>(Weapon)->SetBowState(EBowState::Idle);
	}
}

void ACPlayer::BeginActionWalk()
{
	IsWalking = true;
}

void ACPlayer::EndActionWalk()
{
	IsWalking = false;
}

void ACPlayer::BeginInteractTrigger()
{
	if (RegisteredTrigger)
	{
		RegisteredTrigger->TriggerF(this);
	}
}

void ACPlayer::EndInteractTrigger()
{
}

void ACPlayer::ZoomIn()
{
	ZoomTimeline->Play();
}

void ACPlayer::ZoomOut()
{
	ZoomTimeline->Reverse();
}

void ACPlayer::UISystemText(const FString InText, bool isVisible)
{
	if (auto* const PlayerWidget = Cast<UCPlayerUserWidget>(Widget))
	{
		if (isVisible)
			PlayerWidget->SetSystemTextVisible(InText);
		else
			PlayerWidget->SetSystemTextHidden();
	}
}

void ACPlayer::SetTrigger(bool IsSetting, ACBaseTrigger* AddedTrigger)
{
	if (IsSetting)
	{
		RegisteredTrigger = AddedTrigger;
	}
	else
	{
		RegisteredTrigger = nullptr;
	}
}

void ACPlayer::Zoom(float const Alpha)
{
	SpringArm->TargetArmLength = FMath::Lerp(TargetArmLength, TargetArmLengthOnZoomIn, Alpha);
	SpringArm->SocketOffset = FMath::Lerp(SocketOffset, SocketOffsetOnZoomIn, Alpha);

	Camera->SetFieldOfView(FMath::Lerp(FieldOfView, FieldOfViewOnZoomIn, Alpha));

}

void ACPlayer::StartMousePosRecord()
{
	if (APlayerController* APController = Cast<APlayerController>(GetController()))
	{
		APController->SetMouseLocation(500, 500);
		APController->ClientIgnoreLookInput(true);
	}
	else
		return;

	
	IsNeedMousePos = true;

	if (auto* const PlayerWidget = Cast<UCPlayerUserWidget>(Widget))
	{
		PlayerWidget->ToggleElementImage(false);
	}
}

void ACPlayer::EndMousePosRecord()
{
	if (APlayerController* APController = Cast<APlayerController>(GetController()))
	{
		APController->ResetIgnoreLookInput();
	}

	IsNeedMousePos = false;

	if (auto* const PlayerWidget = Cast<UCPlayerUserWidget>(Widget))
	{
		PlayerWidget->ToggleElementImage(true);
	}
}

void ACPlayer::Damaged(const EElements& InElementType, const float& Damage)
{
	Hp -= Damage;
	ShieldCount--;
}

void ACPlayer::UpdateWidgetElementColor()
{
	if (auto* const PlayerWidget = Cast<UCPlayerUserWidget>(Widget))
	{
		PlayerWidget->UpdateSkillColor(ElementType);
	}
}

void ACPlayer::LevelInit()
{
	Hp = MaxHp;
	Mp = MaxMp;

	UpdateWidgetHP();
	UpdateWidgetMP();
	UpdateWidgetEXP();
	UpdateWidgetLevel();
}

void ACPlayer::LevelUP()
{
	MaxHp = 100 + Level * 50;
	MaxMp = 50 + Level * 25;
	MaxExp = Level * 100;
	
	LevelInit();

}

void ACPlayer::UpdateWidgetHP()
{
	if (auto* const PlayerWidget = Cast<UCPlayerUserWidget>(Widget))
	{
		PlayerWidget->UpdateHP(MaxHp, Hp);
	}
}

void ACPlayer::UpdateWidgetMP()
{
	if (auto* const PlayerWidget = Cast<UCPlayerUserWidget>(Widget))
	{
		PlayerWidget->UpdateMP(MaxMp, Mp);
	}
}

void ACPlayer::UpdateWidgetEXP()
{
	if (auto* const PlayerWidget = Cast<UCPlayerUserWidget>(Widget))
	{
		PlayerWidget->UpdateEXP(MaxExp, Exp);
	}
}

void ACPlayer::UpdateWidgetLevel()
{
	if (auto* const PlayerWidget = Cast<UCPlayerUserWidget>(Widget))
	{
		PlayerWidget->UpdateLevel(Level);
	}
}
