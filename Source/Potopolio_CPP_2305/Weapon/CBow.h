// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/CWeapon.h"
#include "CEnums.h"
#include "Interface/BowInterface.h"
#include "Projectile/CProjectileArrow.h"
#include "CBow.generated.h"

enum class EBowState : uint8;

UCLASS(Abstract)
class POTOPOLIO_CPP_2305_API ACBow
	: public ACWeapon,
	public IBowInterface
{
	GENERATED_BODY()
public:
	ACBow();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;



private:
	void BeginBasicAction() override { BeginDraw(); }
	void EndBasicAction() override { EndDraw(); }
	void BeginIntensiveAction() override { BeginZoom(); }
	void EndIntensiveAction() override { EndZoom(); }

	void BeginElementAction() override;
	bool EndElementAction(const FVector2D& InMousePos) override;

	UFUNCTION()
		void ChangeElementEffect(UAnimMontage* BuffMontage, bool Interrupted);

private:
	void BeginDraw() override;
	void EndDraw() override;
	void BeginZoom() override;
	void EndZoom() override;

	const EBowState GetBowState() override { return BowState; }
	void SetBowState(EBowState InBowState) override;
	void OrderPlayAnimMontage(EBowState InBowState)override;
	ACProjectileArrow* GetArrowModel() override { return ArrowModel; }
	FActorSpawnParameters GetArrowSpawnParameters() override;
	void SetVisiblity(bool IsVisible) override;
	FVector GetArrowVelocity() override;
	FVector InterfaceGetActorLocation() override;


private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		EBowState BowState = EBowState::Idle;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* QuiverMesh;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		FName QuiverSocketName;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class ACProjectile> ArrowModelClass;
	UPROPERTY(meta = (AllowPrivateAccess = "true"))
		class ACProjectileArrow* ArrowModel;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		FName ArrowSocketName;
	UPROPERTY(EditDefaultsOnly)
		FName ArrowSpawnSocketName = NAME_None;

	bool DrawOrderAgain = false;
	bool ElementOrderedIn = false;
};
