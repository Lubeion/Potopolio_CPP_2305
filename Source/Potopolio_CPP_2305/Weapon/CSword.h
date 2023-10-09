// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/CWeapon.h"
#include "Interface/SwordInterface.h"
#include "CSword.generated.h"

/**
 * 
 */


UCLASS(Abstract)
class POTOPOLIO_CPP_2305_API ACSword 
	: public ACWeapon
	, public ISwordInterface
{
	GENERATED_BODY()

public:
	ACSword();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION(BlueprintCallable)
		virtual void SetNewElementVisuality() override;
private:
	void BeginBasicAction() override		{ BeginComboAttack(); }
	void EndBasicAction() override			{ EndComboAttack(); }
	void BeginIntensiveAction() override	{ BeginPowerAttack(); }
	void EndIntensiveAction() override		{ EndPowerAttack(); }

	void BeginElementAction() override;
	bool EndElementAction(const FVector2D& InMousePos) override;
	

public:
	void ActivateAttack(bool Activate) override;

protected:
	UFUNCTION()
		void ChangeElementEffect(UAnimMontage* BuffMontage, bool Interrupted);
	UFUNCTION()
		void EndAttackMontage(UAnimMontage* AttackMontage, bool Interrupted);
	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	UPROPERTY(EditDefaultsOnly)
		class UCapsuleComponent* SwordCollision;
	UPROPERTY(EditDefaultsOnly)
		FName AttachEffectSocketName;
	UPROPERTY(EditDefaultsOnly)
		class UParticleSystemComponent* Trail;
	UPROPERTY(EditDefaultsOnly)
		FName TrailSocketStart;
	UPROPERTY(EditDefaultsOnly)
		FName TrailSocketEnd;
private:
	void BeginComboAttack() override;
	void EndComboAttack() override;
	void BeginPowerAttack() override;
	void EndPowerAttack() override;

	void NextComboAttack() override;
	bool GetNextComboEnabled() override { return NextComboAttackEnabled; }

private:
	bool Enchanted = false;
	float EnchantDuration = 0.0f;
	int ComboCount = 0;
	bool ElementOrderedIn = false;
	bool ComboAttackOrderedIn = false;
	bool PowerAttackOrderedIn = false;
	bool NextComboAttackEnabled = false;

	TSet<ACCharacter*> Targets;
};
