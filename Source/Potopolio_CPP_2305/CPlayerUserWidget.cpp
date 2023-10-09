// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayerUserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/TimelineComponent.h"
#include "Logger.h"

UCPlayerUserWidget::UCPlayerUserWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}
void UCPlayerUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

}

void UCPlayerUserWidget::NativePreConstruct()
{
	Super::NativePreConstruct();


}

void UCPlayerUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HPBar = Cast<UProgressBar>(GetWidgetFromName(NameHPProgressBar));
	MPBar = Cast<UProgressBar>(GetWidgetFromName(NameMPProgressBar));
	EXPBar = Cast<UProgressBar>(GetWidgetFromName(NameEXPProgressBar));
	Skill1Image = Cast<UImage>(GetWidgetFromName(NameSkill1Image));
	Skill2Image = Cast<UImage>(GetWidgetFromName(NameSkill2Image));
	Skill3Image = Cast<UImage>(GetWidgetFromName(NameSkill3Image));
	Skill4Image = Cast<UImage>(GetWidgetFromName(NameSkill4Image));
	SystemText = Cast<UTextBlock>(GetWidgetFromName(NameSystemText));
	FireImage = Cast<UImage>(GetWidgetFromName(NameFireImage));
	EletricImage = Cast<UImage>(GetWidgetFromName(NameEletricImage));
	IceImage = Cast<UImage>(GetWidgetFromName(NameIceImage));
	NoneImage = Cast<UImage>(GetWidgetFromName(NameNoneImage));
	FrontWeaponImage = Cast<UImage>(GetWidgetFromName(NameFrontWeaponImage));
	BackWeaponImage = Cast<UImage>(GetWidgetFromName(NameBackWeaponImage));

}

void UCPlayerUserWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UCPlayerUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (bIsUsingMousePos)
		SetImageSize(InDeltaTime);
}

void UCPlayerUserWidget::UpdateSkillColor(const EElements& InElementType)
{

	FLinearColor Color = FLinearColor::White;
	switch (InElementType)
	{
	case EElements::None:
		break;
	case EElements::Fire:
		Color = FLinearColor::Red;
		break;
	case EElements::Ice:
		Color = FLinearColor::Blue;
		break;
	case EElements::Eletric:
		Color = FLinearColor::Green;
		break;
	case EElements::Max:
		break;
	default:
		break;
	}

	Skill1Image->SetBrushTintColor(FSlateColor(Color));
	Skill2Image->SetBrushTintColor(FSlateColor(Color));
	Skill3Image->SetBrushTintColor(FSlateColor(Color));

}

void UCPlayerUserWidget::UpdateHP(const float& MaxHP, const float& CurHP)
{
	FString HP = FString::SanitizeFloat(CurHP) + " / " + FString::SanitizeFloat(MaxHP);

	HPText = HP;

	HPBar->SetPercent(CurHP / MaxHP);
}

void UCPlayerUserWidget::UpdateMP(const float& MaxMP, const float& CurMP)
{
	FString MP = FString::SanitizeFloat(CurMP) + " / " + FString::SanitizeFloat(MaxMP);

	MPText = MP;

	MPBar->SetPercent(CurMP / MaxMP);
}

void UCPlayerUserWidget::UpdateEXP(const float& MaxEXP, const float& CurEXP)
{
	FString EXP = FString::SanitizeFloat(CurEXP) + " / " + FString::SanitizeFloat(MaxEXP);

	EXPText = EXP;

	EXPBar->SetPercent(CurEXP / MaxEXP);
}

void UCPlayerUserWidget::UpdateLevel(const int& Level)
{
	LevelText = FString::FromInt(Level);
}

void UCPlayerUserWidget::ToggleElementImage(const bool& bHidden)
{
	ESlateVisibility Setting;

	if (bHidden)
	{
		Setting = ESlateVisibility::Hidden;
	}
	else
	{
		Setting = ESlateVisibility::Visible;
	}

	FireImage->SetVisibility(Setting);
	EletricImage->SetVisibility(Setting);
	IceImage->SetVisibility(Setting);
	NoneImage->SetVisibility(Setting);

	bIsUsingMousePos = !bHidden;
}

void UCPlayerUserWidget::SetSystemTextVisible(const FString& Text)
{
	SystemText->SetVisibility(ESlateVisibility::Visible);
	SystemText->SetText(FText::FromString(Text));
}

void UCPlayerUserWidget::SetSystemTextHidden()
{
	SystemText->SetVisibility(ESlateVisibility::Hidden);
	SystemText->SetText(FText::FromString(""));
}

void UCPlayerUserWidget::SetImageSize(const float& DeltaSeconds)
{
	FVector2D Base = FVector2D(500, 500);
	float Distance;
	FVector2D Direction;

	(MousePos - Base).ToDirectionAndLength(Direction, Distance);
	
	if (Distance >= 100)
	{
		bool Condition1 = Direction.X >= Direction.Y;
		bool Condition2 = Direction.X + Direction.Y >= 0;


		if (Condition1 && Condition2) // Right
		{
			if (PreLoopElement != EElements::Ice)
			{
				ResetElementScale(PreLoopElement);
				PreLoopElement = EElements::Ice;
			}
			
			IceImage->SetRenderScale(FVector2D(2));
		}
		else if (Condition1 && !Condition2) // Up
		{
			if (PreLoopElement != EElements::Eletric)
			{
				ResetElementScale(PreLoopElement);
				PreLoopElement = EElements::Eletric;
			}
			EletricImage->SetRenderScale(FVector2D(2));
		}
		else if (!Condition1 && !Condition2) // Left
		{
			if (PreLoopElement != EElements::Fire)
			{
				ResetElementScale(PreLoopElement);
				PreLoopElement = EElements::Fire;
			}
			FireImage->SetRenderScale(FVector2D(2));
		}
		else if (!Condition1 && Condition2) // Down
		{
			if (PreLoopElement != EElements::None)
			{
				ResetElementScale(PreLoopElement);
				PreLoopElement = EElements::None;
			}
			NoneImage->SetRenderScale(FVector2D(2));
			PreLoopElement = EElements::None;
		}
	}
}

void UCPlayerUserWidget::ResetElementScale(const EElements& InElement)
{
	switch (InElement)
	{
	case EElements::None:
		NoneImage->SetRenderScale(FVector2D(1));
		break;
	case EElements::Fire:
		FireImage->SetRenderScale(FVector2D(1));
		break;
	case EElements::Ice:
		IceImage->SetRenderScale(FVector2D(1));
		break;
	case EElements::Eletric:
		EletricImage->SetRenderScale(FVector2D(1));
		break;
	default:
		break;
	}
}

void UCPlayerUserWidget::SetCurWeaponType(const EWeaponType InWeaponType)
{
	switch (InWeaponType)
	{
	case EWeaponType::None:
		break;
	case EWeaponType::Sword:
		FrontWeaponImage->SetBrushFromTexture(SwordImage);
		BackWeaponImage->SetBrushFromTexture(BowImage);
		break;
	case EWeaponType::Bow:
		FrontWeaponImage->SetBrushFromTexture(BowImage);
		BackWeaponImage->SetBrushFromTexture(SwordImage);
		break;
	default:
		break;
	}
}
