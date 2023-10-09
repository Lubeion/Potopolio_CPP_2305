// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/CBow.h"
#include "Character/CPlayer.h"
#include "Interface/PlayerActionInterface.h"

ACBow::ACBow()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SetRootComponent(SK_WeaponMesh);

	QuiverMesh = CreateDefaultSubobject<UStaticMeshComponent>("QuiverMesh");
	QuiverMesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	
}

void ACBow::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	WeaponType = EWeaponType::Bow;

	
}

void ACBow::BeginPlay()
{
	Super::BeginPlay();
	FAttachmentTransformRules const Rules(EAttachmentRule::SnapToTarget, true);
	if (auto* Inst = Cast<ACCharacter>(GetInstigator()))
	{
		QuiverMesh->AttachToComponent(Inst->GetMesh(), Rules, QuiverSocketName);
		if (ArrowModelClass)
		{
			ArrowModel = Cast<ACProjectileArrow>(GetWorld()->SpawnActor(ArrowModelClass, &GetActorTransform(), GetArrowSpawnParameters()));
			ArrowModel->SetActorEnableCollision(false);
			ArrowModel->AttachToComponent(SK_WeaponMesh, Rules, ArrowSpawnSocketName);
			ArrowModel->SetVisiblity(false);
		}
	}

	
}

void ACBow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACBow::BeginElementAction()
{
	ElementOrderedIn = true;
}

bool ACBow::EndElementAction(const FVector2D& InMousePos)
{
	if (!ElementOrderedIn)
		return false;
	ElementOrderedIn = false;

	if (auto* Inst = Cast<ACCharacter>(GetInstigator()))
	{
		if (!Inst->CheckAnimMontagePlayable())
			return false;

		if (!UElementsFunctionLibrary::SelectElement(ElementType, InMousePos))
			return false;

		Inst->SetAnimMontagePlayable(false);

		//UI 끄기
		UMontageFunctionLibrary::PlayAnimMontage(MontageData, "Buff", GetInstigator());
		Inst->GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &ThisClass::ChangeElementEffect);
		
		return true;
	}

	return false;
}

void ACBow::ChangeElementEffect(UAnimMontage* BuffMontage, bool Interrupted)
{
	if (auto* Inst = Cast<ACCharacter>(GetInstigator()))
	{
		Inst->GetMesh()->GetAnimInstance()->OnMontageEnded.RemoveDynamic(this, &ThisClass::ChangeElementEffect);
		Inst->SetAnimMontagePlayable(true);

		ArrowModel->SetNewEffect(ElementType);
	}
}

void ACBow::BeginDraw()
{
	if (auto* Inst = Cast<ACCharacter>(GetInstigator()))
	{
		if (!Inst->CheckAnimMontagePlayable())
			return;

		SetBowState(EBowState::Draw);
	}
}

void ACBow::EndDraw()
{
	if (BowState != EBowState::Pull)
		return;

	BowState = EBowState::Fire;
	FTransform Transform = SK_WeaponMesh->GetSocketTransform(ArrowSpawnSocketName);

	ACProjectile* Arrow = Cast<ACProjectile>(GetWorld()->SpawnActor(
				ArrowModelClass,
				&Transform,
				GetArrowSpawnParameters()));

	Arrow->SetNewEffect(ElementType);
	Arrow->FireProjectile(ArrowModel->GetDirection());
	Arrow->SetOwner(GetOwner());
	Arrow->SetDamage(Damage);
	//Logger::Print(ArrowModel->GetDirection().Vector());

	ArrowModel->SetVisiblity(false);
	
	if (DrawOrderAgain)
	{
		SetBowState(EBowState::Pull);
	}
	else
	{
		SetBowState(EBowState::Idle);
	}
	//Notify 만들고.. BowState 변수로 갖고, 실행될때 바꾸기.....
}

void ACBow::BeginZoom()
{
	if (auto* Inst = Cast<IPlayerActionInterface>(GetInstigator()))
	{
		Inst->ZoomIn();
	}
}

void ACBow::EndZoom()
{
	if (auto* Inst = Cast<IPlayerActionInterface>(GetInstigator()))
	{
		Inst->ZoomOut();
	}
}

void ACBow::SetBowState(EBowState InBowState)
{
	OrderPlayAnimMontage(InBowState);
	BowState = InBowState;
}

void ACBow::OrderPlayAnimMontage(EBowState InBowState)
{
	if (ACCharacter* Inst = Cast<ACCharacter>(GetInstigator()))
	{
		switch (InBowState)
		{
			case EBowState::Idle:
			if (BowState == EBowState::Draw)
			{
				if (UMontageFunctionLibrary::PlayAnimMontage(MontageData, "Aim2Idle", Inst))
				{
					UMontageFunctionLibrary::PlayBowAnimMontage(SK_WeaponMontageData, "Aim2Idle", this);
					Inst->SetAnimMontagePlayable(true);

				}
			}
			else if (BowState == EBowState::Pull)
			{
				if (UMontageFunctionLibrary::PlayAnimMontage(MontageData, "Aim2Idle", Inst))
				{
					UMontageFunctionLibrary::PlayBowAnimMontage(SK_WeaponMontageData, "Aim2Idle", this);
					Inst->SetAnimMontagePlayable(true);
					
				}
			}
			else if (BowState == EBowState::Fire)
			{
				if (UMontageFunctionLibrary::PlayAnimMontage(MontageData, "Shoot2Idle", Inst))
				{
					UMontageFunctionLibrary::PlayBowAnimMontage(SK_WeaponMontageData, "Shoot2Idle", this);
					Inst->SetAnimMontagePlayable(true);
				}
			}
			break;
			case EBowState::Draw:
			if (BowState == EBowState::Idle)
			{
				if (UMontageFunctionLibrary::PlayAnimMontage(MontageData, "Idle2Aim", Inst))
				{
					UMontageFunctionLibrary::PlayBowAnimMontage(SK_WeaponMontageData, "Idle2Aim", this);
					Inst->SetAnimMontagePlayable(false);
				}
			}
			break;
			case EBowState::Pull:
			if (BowState == EBowState::Draw)
			{
				if (UMontageFunctionLibrary::PlayAnimMontage(MontageData, "Aim", Inst))
				{
					UMontageFunctionLibrary::PlayBowAnimMontage(SK_WeaponMontageData, "Aim", this);
				}
			}
			else if (BowState == EBowState::Fire)
			{
				if (UMontageFunctionLibrary::PlayAnimMontage(MontageData, "Shoot2Aim", Inst))
				{
					UMontageFunctionLibrary::PlayBowAnimMontage(SK_WeaponMontageData, "Shoot2Aim", this);
				}
			}
			break;
			case EBowState::Fire:
				if (DrawOrderAgain)
				{
					SetBowState(EBowState::Pull);
				}
				else
				{
					SetBowState(EBowState::Idle);
				}
			break;
			case EBowState::Dead:
				//playmontage Dead..?
			break;
			default:
			break;

		}
	}
}

FActorSpawnParameters ACBow::GetArrowSpawnParameters()
{
	FActorSpawnParameters params;
	params.Owner = GetOwner();
	params.Instigator = GetInstigator();
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	return params;
}

void ACBow::SetVisiblity(bool IsVisible)
{
	Super::SetVisiblity(IsVisible);
	if(ArrowModel)
		ArrowModel->SetVisiblity(IsVisible);
}

FVector ACBow::GetArrowVelocity()
{
	return ArrowModel->GetDirection().GetRightVector() * 3000;
}

FVector ACBow::InterfaceGetActorLocation()
{
	return GetActorLocation();
}
