// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CCharacter.h"
#include "Weapon/CWeapon.h"

#include "CHumanoidCharacter.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EMagics : uint8
{
	None,
	Arrow,
	Circle
};

UCLASS(Abstract)
class POTOPOLIO_CPP_2305_API ACHumanoidCharacter : public ACCharacter
{
	GENERATED_BODY()
	
public:
	ACHumanoidCharacter();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void BeginPlay() override;

public:
	void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		const EElements GetElementType();

	UFUNCTION(BlueprintCallable)
		const EWeaponType GetWeaponType();

	IWeaponInterface* GetWeapon() { return Weapon; }
	IWeaponInterface* GetPreWeapon() {return PreWeapon; }
	const float GetFloatInputDirection();
	const EBowState GetBowState() { return CurBowState; }

	EMagics GetMagicSpellType() { return CurMagicSpell; }
	const FName GetMagicSpawnSocketName();

	UClass* GetMagicClass();
	const float& GetBowAimVertical() { return BowAimVirtical; }
	virtual void SetBowAimVertical(const float& Degree) {}

	const float& GetDamage() { return BaseDamage; }
protected:
	UPROPERTY(EditDefaultsOnly)
		TArray<TSubclassOf<class ACWeapon>> WeaponClasses;
	class IWeaponInterface* Weapon;
	class IWeaponInterface* PreWeapon;
	TArray<decltype(Weapon)> Weapons;
	int CurWeaponIndex = 0;
	int MaxWeaponIndex = -1;

	UPROPERTY(EditDefaultsOnly)
		class UDataTable* MagicMontageData;

	float SpeedMax = 600.0f;
	float SpeedWalk = 300.0f;

	FVector2D InputDirection;
	bool IsWalking = false;
	float BowAimVirtical;
	EBowState CurBowState;

	virtual void BeginAction1() override;
	virtual void EndAction1() override;
	bool Action1OrderedIn = false;
	virtual void BeginAction2() override;
	virtual void EndAction2() override;
	bool Action2OrderedIn = false;
	virtual void BeginAction3() override;
	virtual void EndAction3() override;
	bool Action3OrderedIn = false;
	virtual void BeginAction4() override;
	virtual void EndAction4() override;
	bool Action4OrderedIn = false;

	UFUNCTION()
		void EndMagicMontage(UAnimMontage* BuffMontage, bool Interrupted);

	UPROPERTY(EditDefaultsOnly)
		FName RHMagicSocket;
	UPROPERTY(EditDefaultsOnly)
		FName LHMagicSocket;

protected:
	virtual void BeginActionA() override;
	virtual void EndActionA() override;
	virtual void BeginActionB() override;
	virtual void EndActionB() override;

private:
	EMagics CurMagicSpell = EMagics::None;

};
