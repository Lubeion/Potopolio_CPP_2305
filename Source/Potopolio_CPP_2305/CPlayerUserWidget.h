// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ElementsFunctionLibrary.h"
#include "CEnums.h"
#include "CPlayerUserWidget.generated.h"

/**
 * 
 */

enum class EElements : uint8;
enum class EWeaponType : uint8;

UCLASS(Abstract)
class POTOPOLIO_CPP_2305_API UCPlayerUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UCPlayerUserWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeOnInitialized() override;
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void UpdateSkillColor(const EElements& InElementType);
	void UpdateHP(const float& MaxHP, const float& CurHP);
	void UpdateMP(const float& MaxMP, const float& CurMP);
	void UpdateEXP(const float& MaxEXP, const float& CurEXP);
	void UpdateLevel(const int& Level);
	void ToggleElementImage(const bool& bHidden);

	void SetSystemTextVisible(const FString& Text);
	void SetSystemTextHidden();
	void SetMousePos(FVector2D InMousePos) { MousePos = InMousePos; }

	void SetImageSize(const float& DeltaSeconds);
	void ResetElementScale(const EElements& InElement);
	void SetCurWeaponType(const EWeaponType InWeaponType);

	void SetPotionCount(const int NewCount) { PotionCount = NewCount; }
	void SetArrowCount(const int NewCount) { ArrowCount = NewCount; }

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		FName NameHPProgressBar;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		FName NameMPProgressBar;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		FName NameEXPProgressBar;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		FName NameSkill1Image;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		FName NameSkill2Image;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		FName NameSkill3Image;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		FName NameSkill4Image;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		FName NameSystemText;

	class UProgressBar* HPBar;
	class UProgressBar* MPBar;
	class UProgressBar* EXPBar;
	class UImage* Skill1Image;
	class UImage* Skill2Image;
	class UImage* Skill3Image;
	class UImage* Skill4Image;
	class UTextBlock* SystemText;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		FName NameFireImage;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		FName NameEletricImage;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		FName NameIceImage;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		FName NameNoneImage;

	class UImage* FireImage;
	class UImage* EletricImage;
	class UImage* IceImage;
	class UImage* NoneImage;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		FName NameFrontWeaponImage;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		FName NameBackWeaponImage;

	class UImage* FrontWeaponImage;
	class UImage* BackWeaponImage;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		class UTexture2D* SwordImage;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		class UTexture2D* BowImage;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		int PotionCount;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		int ArrowCount;

	UPROPERTY(BlueprintReadWrite)
		FString HPText = L"0/0";
	UPROPERTY(BlueprintReadWrite)
		FString MPText = L"0/0";
	UPROPERTY(BlueprintReadWrite)
		FString EXPText = L"0/0";
	UPROPERTY(BlueprintReadWrite)
		FString LevelText = L"1";

	FVector2D MousePos;
	EElements PreLoopElement;

	bool bIsUsingMousePos = false;
};
