// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CHumanoidCharacter.h"
#include "Interface/PlayerActionInterface.h"
#include "Actor/CBaseTrigger.h"
#include "CPlayer.generated.h"

/**
 * 
 */
UCLASS()
class POTOPOLIO_CPP_2305_API ACPlayer 
	: public ACHumanoidCharacter
	, public IPlayerActionInterface
{
	GENERATED_BODY()
	
public:
	ACPlayer();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void BeginPlay() override;

	virtual void Landed(FHitResult const& HitResult) override;

public:
	void Tick(float DeltaTime) override;

	void GainEXP(const float& InExp);

protected:
	UFUNCTION()
	void BeginTriggerChecker(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void EndTriggerChecker(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* SpringArm;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UCParkourComponent* ParkourComponent;

private:
	void BeginActionA() override;
	void EndActionA() override;

private:
	void BeginAction1() override;
	void EndAction1() override;
	void BeginAction2() override;
	void EndAction2() override;
	void BeginAction3() override;
	void EndAction3() override;
	void BeginAction4() override;
	void EndAction4() override;

private:
	void BeginActionReturn() override;
	void EndActionReturn() override;
	void BeginActionTargeting() override;
	void EndActionTargeting() override;
	void BeginActionWeaponChange() override;
	void EndActionWeaponChange() override;
	void BeginActionPotion() override;
	void EndActionPotion() override;
	void BeginActionParkour() override;
	void EndActionParkour() override;
	void BeginActionWalk() override;
	void EndActionWalk() override;
	void BeginInteractTrigger() override;
	void EndInteractTrigger() override;
	void SetInputDirection(const FVector2D Direction) override { InputDirection = Direction; }
	void ZoomIn() override;
	void ZoomOut() override;
	void UISystemText(const FString InText, bool isVisible = true) override;
	void SetTrigger(bool IsSetting, ACBaseTrigger* AddedTrigger) override;

private:
	UFUNCTION(meta = (AllowPrivateAccess = "true"))
		void Zoom(float const Alpha);

	void StartMousePosRecord();
	void EndMousePosRecord();
	
	void Damaged(const EElements& InElementType, const float& Damage) override;

	void UpdateWidgetElementColor();

	void LevelInit();
	void LevelUP();

	void UpdateWidgetHP();
	void UpdateWidgetMP();
	void UpdateWidgetEXP();
	void UpdateWidgetLevel();

	/*const FVector TraceArrowLineLocation(const FVector& U, const float& T);
	void TraceArrowLine();*/

private:
	FVector2D MousePos;
	bool IsNeedMousePos = false;

	UPROPERTY(meta = (AllowPrivateAccess = "true"))
		class UTimelineComponent* ZoomTimeline;
	UPROPERTY(EditDefaultsOnly, Category = "Zoom", meta = (AllowPrivateAccess = "true"))
		class UCurveFloat* BlendCurveOnZoomIn;
	UPROPERTY(EditDefaultsOnly, Category = "Zoom", meta = (AllowPrivateAccess = "true"))
		float BlendTimeOnZoomIn;
	UPROPERTY(EditDefaultsOnly, Category = "Zoom", meta = (AllowPrivateAccess = "true"))
		float FieldOfViewOnZoomIn;
	UPROPERTY(EditDefaultsOnly, Category = "Zoom", meta = (AllowPrivateAccess = "true"))
		float TargetArmLengthOnZoomIn;
	UPROPERTY(EditDefaultsOnly, Category = "Zoom", meta = (AllowPrivateAccess = "true"))
		FVector SocketOffsetOnZoomIn;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class UUserWidget> WidgetClass;
	UPROPERTY(EditDefaultsOnly, Category = "Trigger", meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* TriggerChecker;

	class UUserWidget* Widget;

	float FieldOfView;
	float TargetArmLength;
	FVector SocketOffset;

	bool WillDash = false;
	bool IsZoomIn = false;
	bool Action1OrderedIn = false;
	bool Action2OrderedIn = false;
	bool Action3OrderedIn = false;
	bool TraceArrowProjectile = false;

	float Skill1Cost = 10;
	float Skill2Cost = 20;
	float Skill3Cost = 5;

	class ACBaseTrigger* RegisteredTrigger;

};
