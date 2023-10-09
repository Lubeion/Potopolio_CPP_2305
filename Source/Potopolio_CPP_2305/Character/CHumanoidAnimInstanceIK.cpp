// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CHumanoidAnimInstanceIK.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

void UCHumanoidAnimInstanceIK::NativeUpdateAnimation(float const DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (auto* const PawnOwner = TryGetPawnOwner())
	{
		FVector const Velocity = PawnOwner->GetVelocity();
		Direction = CalculateDirection(Velocity, PawnOwner->GetActorRotation());
		Speed = Velocity.Size2D();
		Pitch = PawnOwner->GetBaseAimRotation().Pitch;
		

		if (ACHumanoidCharacter* HOwner = Cast<ACHumanoidCharacter>(PawnOwner))
		{
			WeaponType = HOwner->GetWeaponType();
			InputDirection = HOwner->GetFloatInputDirection();
			SState = HOwner->GetSimpleState();
			BState = HOwner->GetBattleState();
			CurBowState = HOwner->GetBowState();
			BowAimVertical = HOwner->GetBowAimVertical();

			if (BState != EBattleState::Dash)
				DashDirection = InputDirection;
		}

		if (WeaponType == EWeaponType::Bow)
		{
			if (InputDirection >= -90 && InputDirection <= 90)
			{
				IsVelocityForward = true;
			}
			else
			{
				IsVelocityForward = false;
				Direction = -(Direction + (1 - 2 * (int)(Direction > 0)) * 180);
			}
		}


		float DistanceL;
		FRotator RotatorL;
		TraceForIK(IKBoneL, DistanceL, RotatorL);

		float DistanceR;
		FRotator RotatorR;
		TraceForIK(IKBoneR, DistanceR, RotatorR);

		float DistanceP = FMath::Min(DistanceL, DistanceR);

		TranslationP.Z = FMath::FInterpTo(TranslationP.Z, DistanceP, DeltaSeconds, InterpSpeed);
		TranslationL.Z = FMath::FInterpTo(TranslationL.Z, DistanceL - TranslationP.Z, DeltaSeconds, InterpSpeed);
		TranslationR.Z = FMath::FInterpTo(TranslationR.Z, DistanceR - TranslationP.Z, DeltaSeconds, InterpSpeed);

		RotationL = FMath::RInterpTo(RotationL, RotatorL, DeltaSeconds, InterpSpeed);
		RotationR = FMath::RInterpTo(RotationR, RotatorR, DeltaSeconds, InterpSpeed);

	}
}

void UCHumanoidAnimInstanceIK::TraceForIK(FName const Bone, float& Distance, FRotator& Rotator)
{
	FVector const IKTarget = GetOwningComponent()->GetSocketLocation(Bone);
	FVector const IKRoot = GetOwningComponent()->GetSocketLocation(TEXT("Root"));
	FVector const IKActor = GetOwningActor()->GetActorLocation();
	FVector const IKRVector = GetOwningComponent()->GetRightVector();

	FVector const IKStart = { IKTarget.X + IKRVector.X * 7, IKTarget.Y + IKRVector.Y * 7, IKActor.Z - 44 };
	FVector const IKEnd = { IKTarget.X + IKRVector.X * 7, IKTarget.Y + IKRVector.Y * 7, IKRoot.Z - TraceDistance };

	FHitResult IKResult;
	
	UKismetSystemLibrary::BoxTraceSingle(
		GetWorld(),
		IKStart,
		IKEnd,
		FVector(15, 5, 1),
		GetOwningActor()->GetActorRotation(),
		ETraceTypeQuery::TraceTypeQuery1,
		false,
		{ GetOwningActor() },
		EDrawDebugTrace::Type::None,
		IKResult,
		true
	);

	Distance = 0;
	Rotator = FRotator::ZeroRotator;

	if (IKResult.bBlockingHit)
	{
		//Root.Z = Result.TraceEnd.Z + TraceDistance
		Distance = IKResult.Location.Z - IKRoot.Z;

		float const IKRoll = +UKismetMathLibrary::DegAtan2(IKResult.Normal.Y, IKResult.Normal.Z);
		float const IKPitch = -UKismetMathLibrary::DegAtan2(IKResult.Normal.X, IKResult.Normal.Z);

		Rotator = { IKPitch, 0, IKRoll };
	}

	///*if (FVector::Distance(IKResult.Location, IKStart) < 100)
	//	Distance = 0;*/
	//Logger::Print(Distance);
}
