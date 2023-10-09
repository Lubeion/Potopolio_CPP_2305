// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "CParkourComponent.generated.h"


UENUM(BlueprintType)	//블루프린트에서 사용 할 타입
enum class EParkourType : uint8	// <- uint8 자료형, blueprint에서 인식할 수 있는 자료형
{
	None,
	Climb,
	Fall,
	Slide,
	Normal,
	Short,
	Wall,
	Max
};
//EParkourType type = EParkourType::None <- int32 자료형
UENUM(BlueprintType)
enum class EArrowType : uint8
{
	Center,
	Ceil,
	Floor,
	Left,
	Right,
	Land,
	Max
};

USTRUCT(BlueprintType)
struct FParkourData : public FTableRowBase
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere)	EParkourType Type;
	UPROPERTY(EditAnywhere)	class UAnimMontage* Montage;
	UPROPERTY(EditAnywhere) float PlayRate = 1.0f;
	UPROPERTY(EditAnywhere)	FName Section;
	UPROPERTY(EditAnywhere)	float DistMin;
	UPROPERTY(EditAnywhere) float DistMax;
	UPROPERTY(EditAnywhere)	float Extent;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POTOPOLIO_CPP_2305_API UCParkourComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCParkourComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


public:
	bool BeginParkour();
	UFUNCTION()
		void EndParkour(UAnimMontage* const Montage, bool bInterrupted);

private:
	void TraceArrow(EArrowType const Type);
	void TraceCenter();
	void TraceLand();

	bool CheckObstacle();

	bool CheckClimb();
	void BeginClimb();
	void EndClimb();

	bool CheckFall();
	void BeginFall();
	void EndFall();

	bool CheckSlide();
	void BeginSlide();
	void EndSlide();

	bool CheckOthers(EParkourType const Type, FParkourData& Data);
	void BeginOthers(EParkourType const Type, FParkourData const& Data);
	void EndOthers();


private:
	UPROPERTY(EditDefaultsOnly)
		class UDataTable* DataTable;

	TMap<EParkourType, TArray<FParkourData>> DataMap;

	class UArrowComponent* Arrows[int32(EArrowType::Max)];

	FHitResult Results[int32(EArrowType::Max)];

	float TraceDistance = 500;
	float AcceptableAngle = 45;

	AActor* HitObstacle;
	FVector HitObstacleExtent;
	float HitDistance;
	float Yaw;

	bool bFalling;

	AActor* Target;


	EParkourType ParkourType = EParkourType::None;
};
