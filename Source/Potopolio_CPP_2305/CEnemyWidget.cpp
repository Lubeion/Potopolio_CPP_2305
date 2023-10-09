// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemyWidget.h"
#include "Logger.h"

UCEnemyWidget::UCEnemyWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}

void UCEnemyWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

}

void UCEnemyWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

}

void UCEnemyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	switch (ElementType)
	{
	case EElements::Fire:
		ShieldColor = FLinearColor::Red;
		break;
	case EElements::Ice:
		ShieldColor = FLinearColor::Blue;
		break;
	case EElements::Eletric:
		ShieldColor = FLinearColor::Green;
		break;
	default:
		ShieldColor = FLinearColor::Gray;
		break;
	}

}

void UCEnemyWidget::NativeDestruct()
{
	Super::NativeDestruct();

}

void UCEnemyWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}
