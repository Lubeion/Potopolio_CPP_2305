// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ElementsFunctionLibrary.h"
#include "Math/Color.h"
#include "CEnemyWidget.generated.h"

enum class EElements :uint8;
/**
 * 
 */
UCLASS(Abstract)
class POTOPOLIO_CPP_2305_API UCEnemyWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UCEnemyWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeOnInitialized() override;
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void UpdateHP(const float& CurHP, const float& MaxHP) { HPPercent = CurHP / MaxHP; }
	void UpdateShield(const int& CurShield, const int& MaxShield) { ShieldPercent = (float)CurShield / MaxShield; }
	void SetElementType(const EElements& InElementType) { ElementType = InElementType; }
	void SetLevel(const int& InLevel) { LevelText = FString::FromInt(InLevel); }
protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		float HPPercent;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		float ShieldPercent;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		FString LevelText;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		EElements ElementType;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		FLinearColor ShieldColor;
};
