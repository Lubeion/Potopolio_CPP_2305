// Fill out your copyright notice in the Description page of Project Settings.


#include "CWeapon.h"



// Sets default values
ACWeapon::ACWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("WeaponMesh");
	SK_WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SK_WeaponMesh");

	WeaponMesh_UnGrapped = CreateDefaultSubobject<UStaticMeshComponent>("WeaponMesh_UnGrapped");
	SK_WeaponMesh_UnGrapped = CreateDefaultSubobject<USkeletalMeshComponent>("SK_WeaponMesh_UnGrapped");

	WeaponMesh_UnGrapped->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	SK_WeaponMesh_UnGrapped->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);

	SetRootComponent(WeaponMesh);

}

void ACWeapon::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	UElementsFunctionLibrary::SetMaterialInstance(ElementWeaponData, ElementType, WeaponMesh);

}
// Called when the game starts or when spawned
void ACWeapon::BeginPlay()
{
	Super::BeginPlay();

	SetVisiblity(false);

	FAttachmentTransformRules const Rules(EAttachmentRule::SnapToTarget, true);
	SK_WeaponMesh_UnGrapped->AttachToComponent(Cast<ACharacter>(GetInstigator())->GetMesh(), Rules, SocketName_UnGrapped);
	WeaponMesh_UnGrapped->AttachToComponent(Cast<ACharacter>(GetInstigator())->GetMesh(), Rules, SocketName_UnGrapped);
}

void ACWeapon::SetNewElementVisuality()
{
	UElementsFunctionLibrary::SetMaterialInstance(ElementWeaponData, ElementType, WeaponMesh);
}


// Called every frame
void ACWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ACWeapon::EquipWeapon()
{
	if (ACCharacter* Inst = Cast<ACCharacter>(GetInstigator()))
	{
		//Inst->SetCurWapon(this)...
		if (Inst->CheckAnimMontagePlayable())
		{
			if (UMontageFunctionLibrary::PlayAnimMontage(MontageData, "Equip", GetInstigator()))
			{
				Inst->SetAnimMontagePlayable(false);
				Inst->GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &ThisClass::EndEquipMontage);
				return true;
			}
		}
	}
	
	return false;
}

bool ACWeapon::UnequipWeapon()
{
	if (ACCharacter* Inst = Cast<ACCharacter>(GetInstigator()))
	{
		//Inst->SetCurWapon(this)...
		if (Inst->CheckAnimMontagePlayable())
		{
			if (UMontageFunctionLibrary::PlayAnimMontage(MontageData, "Unequip", GetInstigator()))
			{
				Inst->SetAnimMontagePlayable(false);

				Inst->GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &ThisClass::EndUnequipMontage);

				return true;
			}
		}
	}

	return false;
}

void ACWeapon::EndUnequipWeaponEvent()
{
	if (ACCharacter* Inst = Cast<ACCharacter>(GetInstigator()))
	{
		Inst->GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &ThisClass::CallEquipMontage);
	}
}

void ACWeapon::SetVisiblity(bool IsVisible)
{
	WeaponMesh->SetVisibility(IsVisible);
	SK_WeaponMesh->SetVisibility(IsVisible);
	WeaponMesh_UnGrapped->SetVisibility(!IsVisible);
	SK_WeaponMesh_UnGrapped->SetVisibility(!IsVisible);
}

void ACWeapon::EndEquipMontage(UAnimMontage* AttackMontage, bool Interrupted)
{
	if (ACCharacter* Inst = Cast<ACCharacter>(GetInstigator()))
	{
		Inst->GetMesh()->GetAnimInstance()->OnMontageEnded.RemoveDynamic(this, &ThisClass::CallEquipMontage);

		Inst->GetMesh()->GetAnimInstance()->OnMontageEnded.RemoveDynamic(this, &ThisClass::EndEquipMontage);
		

		if (Inst->GetBattleState() > EBattleState::Dash)
			return;
		Inst->SetAnimMontagePlayable(true);
	}
}

void ACWeapon::EndUnequipMontage(UAnimMontage* AttackMontage, bool Interrupted)
{
	if (ACCharacter* Inst = Cast<ACCharacter>(GetInstigator()))
	{
		Inst->GetMesh()->GetAnimInstance()->OnMontageEnded.RemoveDynamic(this, &ThisClass::EndUnequipMontage);
		//SetVisiblity(false);

		if (Inst->GetBattleState() > EBattleState::Dash)
			return;
		Inst->SetAnimMontagePlayable(true);
	}
}

void ACWeapon::CallEquipMontage(UAnimMontage* AttackMontage, bool Interrupted)
{
	EquipWeapon();
}



