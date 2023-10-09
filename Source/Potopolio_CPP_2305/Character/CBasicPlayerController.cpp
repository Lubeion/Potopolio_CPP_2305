// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CBasicPlayerController.h"
#include "Interface/CommonActionInterface.h"
#include "Interface/PlayerActionInterface.h"
#include "Logger.h"

void ACBasicPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &ThisClass::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ThisClass::MoveRight);
	InputComponent->BindAxis("LookUp", this, &ThisClass::AddPitchInput);
	InputComponent->BindAxis("LookHorizon", this, &ThisClass::AddYawInput);

	//IActionInterface
	InputComponent->BindAction("LBClick", IE_Pressed, this, &ThisClass::BeginLClick);
	InputComponent->BindAction("LBClick", IE_Released, this, &ThisClass::EndLClick);
	InputComponent->BindAction("RBClick", IE_Pressed, this, &ThisClass::BeginRClick);
	InputComponent->BindAction("RBClick", IE_Released, this, &ThisClass::EndRClick);

	InputComponent->BindAction("ButtonOne", IE_Pressed, this, &ThisClass::BeginNum1);
	InputComponent->BindAction("ButtonOne", IE_Released, this, &ThisClass::EndNum1);
	InputComponent->BindAction("ButtonTwo", IE_Pressed, this, &ThisClass::BeginNum2);
	InputComponent->BindAction("ButtonTwo", IE_Released, this, &ThisClass::EndNum2);
	InputComponent->BindAction("ButtonThree", IE_Pressed, this, &ThisClass::BeginNum3);
	InputComponent->BindAction("ButtonThree", IE_Released, this, &ThisClass::EndNum3);
	InputComponent->BindAction("ButtonFour", IE_Pressed, this, &ThisClass::BeginNum4);
	InputComponent->BindAction("ButtonFour", IE_Released, this, &ThisClass::EndNum4);

	//IPlayerActionInterface
	InputComponent->BindAction("ButtonB", IE_Pressed, this, &ThisClass::BeginBButton);
	InputComponent->BindAction("ButtonB", IE_Released, this, &ThisClass::EndBButton);
	InputComponent->BindAction("ButtonQ", IE_Pressed, this, &ThisClass::BeginQButton);
	InputComponent->BindAction("ButtonQ", IE_Released, this, &ThisClass::EndQButton);
	InputComponent->BindAction("ButtonE", IE_Pressed, this, &ThisClass::BeginEButton);
	InputComponent->BindAction("ButtonE", IE_Released, this, &ThisClass::EndEButton);
	InputComponent->BindAction("ButtonR", IE_Pressed, this, &ThisClass::BeginRButton);
	InputComponent->BindAction("ButtonR", IE_Released, this, &ThisClass::EndRButton);
	InputComponent->BindAction("ButtonF", IE_Pressed, this, &ThisClass::BeginFButton);
	InputComponent->BindAction("ButtonF", IE_Released, this, &ThisClass::EndFButton);
	InputComponent->BindAction("ButtonSpace", IE_Pressed, this, &ThisClass::BeginSpaceButton);
	InputComponent->BindAction("ButtonSpace", IE_Released, this, &ThisClass::EndSpaceButton);
	InputComponent->BindAction("ButtonLShift", IE_Pressed, this, &ThisClass::BeginLShiftButton);
	InputComponent->BindAction("ButtonLShift", IE_Released, this, &ThisClass::EndLShiftButton);
}

void ACBasicPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (auto* const ControlledPawn = GetPawn())
	{
		if (InputDirection.IsZero())
			Cast<IPlayerActionInterface>(ControlledPawn)->SetInputDirection(FVector2D(-1, 0));
		else
			Cast<IPlayerActionInterface>(ControlledPawn)->SetInputDirection(InputDirection);
	}
	
}

void ACBasicPlayerController::MoveForward(const float Value)
{
	if (auto* const ControlledPawn = GetPawn())
	{
		FVector const Direction = FRotator(0, GetControlRotation().Yaw, 0).Quaternion().GetForwardVector();
		ControlledPawn->AddMovementInput(Direction, Value);
		InputDirection.X = Value;
	}
}

void ACBasicPlayerController::MoveRight(const float Value)
{
	if (auto* const ControlledPawn = GetPawn())
	{
		FVector const Direction = FRotator(0, GetControlRotation().Yaw, 0).Quaternion().GetRightVector();
		ControlledPawn->AddMovementInput(Direction, Value);
		InputDirection.Y = Value;
	}
}

void ACBasicPlayerController::BeginLClick()
{
	Cast<ICommonActionInterface>(GetPawn())->BeginActionA();
}

void ACBasicPlayerController::EndLClick()
{
	Cast<ICommonActionInterface>(GetPawn())->EndActionA();
}

void ACBasicPlayerController::BeginRClick()
{
	Cast<ICommonActionInterface>(GetPawn())->BeginActionB();
}

void ACBasicPlayerController::EndRClick()
{
	Cast<ICommonActionInterface>(GetPawn())->EndActionB();
}

void ACBasicPlayerController::BeginNum1()
{
	Cast<ICommonActionInterface>(GetPawn())->BeginAction1();
}

void ACBasicPlayerController::EndNum1()
{
	Cast<ICommonActionInterface>(GetPawn())->EndAction1();
}

void ACBasicPlayerController::BeginNum2()
{
	Cast<ICommonActionInterface>(GetPawn())->BeginAction2();
}

void ACBasicPlayerController::EndNum2()
{
	Cast<ICommonActionInterface>(GetPawn())->EndAction2();
}

void ACBasicPlayerController::BeginNum3()
{
	Cast<ICommonActionInterface>(GetPawn())->BeginAction3();
}

void ACBasicPlayerController::EndNum3()
{
	Cast<ICommonActionInterface>(GetPawn())->EndAction3();
}

void ACBasicPlayerController::BeginNum4()
{
	Cast<ICommonActionInterface>(GetPawn())->BeginAction4();
}

void ACBasicPlayerController::EndNum4()
{
	Cast<ICommonActionInterface>(GetPawn())->EndAction4();
}

void ACBasicPlayerController::BeginBButton()
{
	Cast<IPlayerActionInterface>(GetPawn())->BeginActionReturn();
}

void ACBasicPlayerController::EndBButton()
{
	Cast<IPlayerActionInterface>(GetPawn())->EndActionReturn();
}

void ACBasicPlayerController::BeginQButton()
{
	Cast<IPlayerActionInterface>(GetPawn())->BeginActionTargeting();
}

void ACBasicPlayerController::EndQButton()
{
	Cast<IPlayerActionInterface>(GetPawn())->EndActionTargeting();
}

void ACBasicPlayerController::BeginEButton()
{
	Cast<IPlayerActionInterface>(GetPawn())->BeginActionWeaponChange();
}

void ACBasicPlayerController::EndEButton()
{
	Cast<IPlayerActionInterface>(GetPawn())->EndActionWeaponChange();
}

void ACBasicPlayerController::BeginRButton()
{
	Cast<IPlayerActionInterface>(GetPawn())->BeginActionPotion();
}

void ACBasicPlayerController::EndRButton()
{
	Cast<IPlayerActionInterface>(GetPawn())->EndActionPotion();
}

void ACBasicPlayerController::BeginFButton()
{
	Cast<IPlayerActionInterface>(GetPawn())->BeginInteractTrigger();
}

void ACBasicPlayerController::EndFButton()
{
	Cast<IPlayerActionInterface>(GetPawn())->EndInteractTrigger();
}

void ACBasicPlayerController::BeginSpaceButton()
{
	Cast<IPlayerActionInterface>(GetPawn())->BeginActionParkour();
}

void ACBasicPlayerController::EndSpaceButton()
{
	Cast<IPlayerActionInterface>(GetPawn())->EndActionParkour();
}

void ACBasicPlayerController::BeginLShiftButton()
{
	Cast<IPlayerActionInterface>(GetPawn())->BeginActionWalk();
}

void ACBasicPlayerController::EndLShiftButton()
{
	Cast<IPlayerActionInterface>(GetPawn())->EndActionWalk();
}
