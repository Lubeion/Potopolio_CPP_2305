// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CBasicPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class POTOPOLIO_CPP_2305_API ACBasicPlayerController 
	: public APlayerController
{
	GENERATED_BODY()

public :
	void Tick(float DeltaSeconds) override;

private:
	void SetupInputComponent() override;

	void MoveForward(const float Value);
	void MoveRight(const float Value);

private: // IActionInterface
	void BeginLClick();
	void EndLClick();
	void BeginRClick();
	void EndRClick();

	void BeginNum1();
	void EndNum1();
	void BeginNum2();
	void EndNum2();
	void BeginNum3();
	void EndNum3();
	void BeginNum4();
	void EndNum4();

private: // IPlayerActionInterface
	void BeginBButton();
	void EndBButton();
	void BeginQButton();
	void EndQButton();
	void BeginEButton();
	void EndEButton();
	void BeginRButton();
	void EndRButton();
	void BeginFButton();
	void EndFButton();
	void BeginSpaceButton();
	void EndSpaceButton();
	void BeginLShiftButton();
	void EndLShiftButton();

private:
	FVector2D InputDirection;
};
