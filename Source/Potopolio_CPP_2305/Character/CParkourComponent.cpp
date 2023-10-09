// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CParkourComponent.h"
#include "Character/CCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Logger.h"
#include "Animation/AnimInstance.h"

// Sets default values for this component's properties
UCParkourComponent::UCParkourComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	for (int32 i = 0; i < int32(EArrowType::Max); i++)
	{
		Arrows[i] = CreateDefaultSubobject<UArrowComponent>(FName("Arrow" + FString::FromInt(i)));

	}

	Arrows[int32(EArrowType::Ceil)]->SetRelativeLocation(FVector(0, 0, 80));
	Arrows[int32(EArrowType::Floor)]->SetRelativeLocation(FVector(0, 0, -80));
	Arrows[int32(EArrowType::Left)]->SetRelativeLocation(FVector(0, 30, 0));
	Arrows[int32(EArrowType::Right)]->SetRelativeLocation(FVector(0, -30, 0));
	Arrows[int32(EArrowType::Land)]->SetRelativeLocation(FVector(200, 0, 100));
	Arrows[int32(EArrowType::Land)]->SetRelativeRotation(FRotator(-90, 0, 0));
}


// Called when the game starts
void UCParkourComponent::BeginPlay()
{
	Super::BeginPlay();

	for (int32 i = 0; i < int32(EArrowType::Max); i++)
	{
		FAttachmentTransformRules const Rules(EAttachmentRule::KeepRelative, true);
		Arrows[i]->AttachToComponent(GetOwner()->GetRootComponent(), Rules);
	}

	if (DataTable)
	{
		TArray<FParkourData const*> Rows;

		DataTable->GetAllRows("", Rows);

		for (int32 Key = int32(EParkourType::Climb); Key < int32(EParkourType::Max); ++Key)
		{
			TArray<FParkourData> Value;

			for (FParkourData const* Row : Rows)
				if (Row->Type == EParkourType(Key))
					Value.Add(*Row);

			DataMap.Add(EParkourType(Key), Value);
		}
	}
}


// Called every frame
void UCParkourComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TraceCenter();

	if (HitObstacle)
	{
		TraceArrow(EArrowType::Ceil);
		TraceArrow(EArrowType::Floor);
		TraceArrow(EArrowType::Left);
		TraceArrow(EArrowType::Right);

	}

	TraceLand();
}

bool UCParkourComponent::BeginParkour()
{
	if (ParkourType != EParkourType::None)
		return false;

	if (ACCharacter* const Owner = Cast<ACCharacter>(GetOwner()))
	{
		if (Owner->GetSimpleState() > ESimpleState::Battle)
			return false;

		if (Owner->GetBattleState() < EBattleState::Hit)
			Owner->SetAnimMontagePlayable(true);

		if (!Owner->CheckAnimMontagePlayable())
			return false;

		if (Owner->GetCharacterMovement()->Velocity.Z < -500)
		{
			if (CheckFall())
			{
				BeginFall();
				return true;
			}

		}
	}

	if (CheckObstacle())
	{
		if (CheckClimb())
		{
			BeginClimb();
			return true;
		}
		else if (CheckSlide())
		{
			BeginSlide();
			return true;
		}
		else
		{
			if (!Results[int32(EArrowType::Ceil)].bBlockingHit)
			{
				float const Dot = FVector::DotProduct
				(
					Results[int32(EArrowType::Center)].Normal,
					HitObstacle->GetActorForwardVector()
				);
				if (FMath::IsNearlyZero(Dot, 0.1f) /*|| FMath::IsNearlyEqual(1.0f, abs(Dot), 0.1f)*/)
				{
					for (int32 i = int32(EParkourType::Normal); i < int32(EParkourType::Max); i++)
					{
						FParkourData Data;

						if (CheckOthers(EParkourType(i), Data))
						{
							BeginOthers(EParkourType(i), Data);
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

void UCParkourComponent::EndParkour(UAnimMontage* const Montage, bool bInterrupted)
{
	Cast<ACCharacter>(GetOwner())->GetMesh()->GetAnimInstance()->OnMontageEnded.RemoveDynamic(this, &ThisClass::EndParkour);

	switch (ParkourType)
	{
	case EParkourType::Climb:
		EndClimb();
		break;
	case EParkourType::Fall:
		EndFall();
		break;
	case EParkourType::Slide:
		EndSlide();
		break;
	case EParkourType::Normal:
	case EParkourType::Short:
	case EParkourType::Wall:
		EndOthers();
		break;
	}

	ParkourType = EParkourType::None;

	if (ACCharacter* const  Player = Cast<ACCharacter>(GetOwner()))
	{
		Player->SetAnimMontagePlayable(true);

		Player->GetController()->ResetIgnoreLookInput();
	}
}

void UCParkourComponent::TraceArrow(EArrowType const Type)
{
	UArrowComponent* const Arrow = Arrows[int32(Type)];
	FTransform const Transform = Arrow->GetComponentToWorld();
	FVector const Start = Transform.GetLocation();
	FVector const End = Start + GetOwner()->GetActorForwardVector() * TraceDistance;

	UKismetSystemLibrary::LineTraceSingle(
		GetWorld(),
		Start,
		End,
		ETraceTypeQuery::TraceTypeQuery1,
		false,
		{ GetOwner() },
		EDrawDebugTrace::None,
		Results[int32(Type)],
		true
	);
}

void UCParkourComponent::TraceCenter()
{
	HitObstacle = nullptr;
	HitObstacleExtent = FVector::ZeroVector;
	HitDistance = 0;
	Yaw = 0;

	TraceArrow(EArrowType::Center);

	FHitResult const& Result = Results[int32(EArrowType::Center)];

	if (Result.bBlockingHit && Result.GetActor())
	{
		typedef UStaticMeshComponent MeshType;
		if (MeshType const* const Mesh = Cast<MeshType>(Result.Actor->GetComponentByClass(MeshType::StaticClass())))
		{
			HitObstacle = Result.GetActor();

			FVector Min, Max;
			//큐브의 두 점
			Mesh->GetLocalBounds(Min, Max);
			//큐브의 길이 * Scale
			HitObstacleExtent = FVector(Max.X - Min.X, Max.Y - Min.Y, Max.Z - Min.Z) * HitObstacle->GetActorScale3D();
			HitDistance = Result.Distance;
			Yaw = UKismetMathLibrary::MakeRotFromX(-Result.Normal).Yaw;

		}

	}
}

void UCParkourComponent::TraceLand()
{
	if (Cast<ACCharacter>(GetOwner())->GetCharacterMovement()->IsFalling() && !bFalling)
	{
		bFalling = true;

		FVector const Start = Arrows[int32(EArrowType::Land)]->GetComponentToWorld().GetLocation();
		FVector const End = Start + Arrows[int32(EArrowType::Land)]->GetComponentToWorld().GetRotation().GetForwardVector() * DataMap[EParkourType::Fall][0].Extent;

		UKismetSystemLibrary::LineTraceSingle(
			GetWorld(),
			Start,
			End,
			ETraceTypeQuery::TraceTypeQuery1,
			false,
			{ GetOwner() },
			EDrawDebugTrace::None,
			Results[int32(EArrowType::Land)],
			true
		);
	}
}

bool UCParkourComponent::CheckObstacle()
{
	bool bResult = true;

	bResult &= Results[int32(EArrowType::Center)].bBlockingHit;
	bResult &= Results[int32(EArrowType::Left)].bBlockingHit;
	bResult &= Results[int32(EArrowType::Right)].bBlockingHit;

	if (bResult)
	{
		FVector const Center = Results[int32(EArrowType::Center)].Normal;
		FVector const Left = Results[int32(EArrowType::Left)].Normal;
		FVector const Right = Results[int32(EArrowType::Right)].Normal;

		if (!Center.Equals(Left) || !Center.Equals(Right))
			return false;

		FVector const Start = Results[int32(EArrowType::Center)].Location;
		FVector const End = GetOwner()->GetActorLocation();

		float const LookAtYaw = UKismetMathLibrary::FindLookAtRotation(Start, End).Yaw;
		float const NormalYaw = UKismetMathLibrary::MakeRotFromX(Center).Yaw;

		if (abs(abs(LookAtYaw) - abs(NormalYaw)) <= AcceptableAngle)
			return true;
	}

	return false;
}

bool UCParkourComponent::CheckClimb()
{
	if (Results[int32(EArrowType::Ceil)].bBlockingHit)
	{
		TArray<FParkourData> const& Data = DataMap[EParkourType::Climb];

		if (Data[0].DistMin <= HitDistance && HitDistance <= Data[0].DistMax)
		{
			if (FMath::IsNearlyEqual(Data[0].Extent, HitObstacleExtent.Z, 10))
				return true;
		}
		else if (Data[0].DistMin > HitDistance)
		{
			GetOwner()->SetActorLocation(GetOwner()->GetActorLocation() - GetOwner()->GetActorForwardVector() * (Data[0].DistMin - HitDistance));
			if (FMath::IsNearlyEqual(Data[0].Extent, HitObstacleExtent.Z, 10))
				return true;
		}

	}

	return false;
}

void UCParkourComponent::BeginClimb()
{
	ParkourType = EParkourType::Climb;

	ACCharacter* const Owner = Cast<ACCharacter>(GetOwner());

	Owner->SetActorLocation(Results[int32(EArrowType::Center)].Location);
	Owner->SetActorRotation(FRotator(0, Yaw, 0));

	TArray<FParkourData> const& Data = DataMap[EParkourType::Climb];

	Owner->PlayAnimMontage(Data[0].Montage, Data[0].PlayRate, Data[0].Section);
	Cast<ACCharacter>(GetOwner())->GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &ThisClass::EndParkour);

	Owner->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);

	Owner->SetAnimMontagePlayable(false);

	Owner->GetController()->SetIgnoreLookInput(true);
}

void UCParkourComponent::EndClimb()
{
	Cast<ACCharacter>(GetOwner())->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

}

bool UCParkourComponent::CheckFall()
{
	if (!bFalling)
		return false;

	bFalling = false;

	float const Distance = Results[int32(EArrowType::Land)].Distance;

	TArray<FParkourData> const& DataArray = DataMap[EParkourType::Fall];

	if (DataArray[0].DistMin <= Distance && Distance <= DataArray[0].DistMax)
		return true;

	return true;
}

void UCParkourComponent::BeginFall()
{
	ParkourType = EParkourType::Fall;

	ACCharacter* const Owner = Cast<ACCharacter>(GetOwner());

	TArray<FParkourData> const& DataArray = DataMap[ParkourType];

	Cast<ACharacter>(GetOwner())->PlayAnimMontage(DataArray[0].Montage, DataArray[0].PlayRate, DataArray[0].Section);
	Cast<ACCharacter>(GetOwner())->GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &ThisClass::EndParkour);

	Owner->SetAnimMontagePlayable(false);

	Owner->GetController()->SetIgnoreLookInput(true);

}

void UCParkourComponent::EndFall()
{
	ParkourType = EParkourType::None;

}

bool UCParkourComponent::CheckSlide()
{
	if (!Results[int32(EArrowType::Floor)].bBlockingHit)
	{
		TArray<FParkourData> const& DataArray = DataMap[EParkourType::Slide];

		if (DataArray[0].DistMin <= HitDistance && HitDistance <= DataArray[0].DistMax)
		{
			FVector const Start = Arrows[int32(EArrowType::Floor)]->GetComponentToWorld().GetLocation() + FVector(0, 0, DataArray[0].Extent);
			FVector const End = Start + GetOwner()->GetActorForwardVector() * TraceDistance;

			bool const Result = UKismetSystemLibrary::BoxTraceSingle(
				GetWorld(),
				Start,
				End,
				FVector(0, DataArray[0].Extent, DataArray[0].Extent),
				GetOwner()->GetActorRotation(),
				ETraceTypeQuery::TraceTypeQuery1,
				false,
				{ GetOwner() },
				EDrawDebugTrace::None,
				Results[int32(EArrowType::Floor)],
				true
			);

			if (Result || Cast<ACCharacter>(GetOwner())->GetCharacterMovement()->Velocity.Size2D() < 450)
				return false;
			else
				return true;
		}
		else if (DataArray[0].DistMin > HitDistance)
		{
			GetOwner()->SetActorLocation(GetOwner()->GetActorLocation() - GetOwner()->GetActorForwardVector() * (DataArray[0].DistMin - HitDistance));

			FVector const Start = Arrows[int32(EArrowType::Floor)]->GetComponentToWorld().GetLocation() + FVector(0, 0, DataArray[0].Extent);
			FVector const End = Start + GetOwner()->GetActorForwardVector() * TraceDistance;

			bool const Result = UKismetSystemLibrary::BoxTraceSingle(
				GetWorld(),
				Start,
				End,
				FVector(0, DataArray[0].Extent, DataArray[0].Extent),
				GetOwner()->GetActorRotation(),
				ETraceTypeQuery::TraceTypeQuery1,
				false,
				{ GetOwner() },
				EDrawDebugTrace::None,
				Results[int32(EArrowType::Floor)],
				true
			);

			if (Result || Cast<ACCharacter>(GetOwner())->GetCharacterMovement()->Velocity.Size2D() < 450)
				return false;
			else
				return true;
		}
	}
	return false;
}

void UCParkourComponent::BeginSlide()
{
	ParkourType = EParkourType::Slide;

	TArray<FParkourData> const& DataArray = DataMap[ParkourType];

	ACCharacter* const Owner = Cast<ACCharacter>(GetOwner());

	Owner->PlayAnimMontage(DataArray[0].Montage, DataArray[0].PlayRate, DataArray[0].Section);
	Cast<ACCharacter>(GetOwner())->GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &ThisClass::EndParkour);

	Target = HitObstacle;
	Target->SetActorEnableCollision(false);

	Owner->SetAnimMontagePlayable(false);

	Owner->GetController()->SetIgnoreLookInput(true);

}

void UCParkourComponent::EndSlide()
{
	Target->SetActorEnableCollision(true);
	Target = nullptr;
}

bool UCParkourComponent::CheckOthers(EParkourType const Type, FParkourData& Data)
{
	TArray<FParkourData> const& DataArray = DataMap[Type];
	for (int32 i = 0; i < DataArray.Num(); ++i)
	{

		if (FMath::IsNearlyEqual(DataArray[i].Extent, HitObstacleExtent.Y, 10))
		{
			if (DataArray[i].DistMin <= HitDistance && HitDistance <= DataArray[i].DistMax)
			{
				Data = DataArray[i];

				return true;
			}
			else if (DataArray[i].DistMin > HitDistance)
			{
				GetOwner()->SetActorLocation(GetOwner()->GetActorLocation() - GetOwner()->GetActorForwardVector() * (DataArray[0].DistMin - HitDistance));

				Data = DataArray[i];

				return true;
			}
			else
				continue;
		}
	}
	return false;
}

void UCParkourComponent::BeginOthers(EParkourType const Type, FParkourData const& Data)
{
	ParkourType = Type;
	ACCharacter* const Owner = Cast<ACCharacter>(GetOwner());

	Owner->SetActorRotation(FRotator(0, Yaw, 0));

	Owner->PlayAnimMontage(Data.Montage, Data.PlayRate, Data.Section);
	Target = HitObstacle;
	Target->SetActorEnableCollision(false);
	Cast<ACCharacter>(GetOwner())->GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &ThisClass::EndParkour);

	Owner->SetAnimMontagePlayable(false);

	Owner->GetController()->SetIgnoreLookInput(true);

}

void UCParkourComponent::EndOthers()
{
	Target->SetActorEnableCollision(true);
	Target = nullptr;
}

