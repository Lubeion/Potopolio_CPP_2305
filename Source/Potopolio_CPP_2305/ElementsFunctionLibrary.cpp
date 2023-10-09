// Fill out your copyright notice in the Description page of Project Settings.


#include "ElementsFunctionLibrary.h"
#include "Materials/MaterialInstance.h"

#include "Logger.h"

float UElementsFunctionLibrary::MinSelectDist = 100.0f;
EElements UElementsFunctionLibrary::PreElementData = EElements::None;

void UElementsFunctionLibrary::SetMaterialInstance(const UDataTable* Data, const EElements& OtherElement, UStaticMeshComponent* Mesh)
{
	if (Data != nullptr)
	{
		TArray<FElementMaterialInstanceData const*> Rows;
		Data->GetAllRows("", Rows);
	
		for (uint32 i = 0; i < uint32(EElements::Max); i++)
			if (Rows[i]->Element == OtherElement)
			{
				Mesh->SetMaterial(0, Rows[i]->MaterialInstance);
				return;
			}
	}
}

void UElementsFunctionLibrary::SetParticle(const UDataTable* Data, const EElements& OtherElement, UParticleSystemComponent* Particle)
{
	if (Data != nullptr)
	{
		TArray< FElementParticleData const*> Rows;
		Data->GetAllRows("", Rows);

		for (uint32 i = 0; i < uint32(EElements::Max); i++)
		{
			if (Rows[i]->Element == OtherElement)
			{
				if (Rows[i]->ParticleSystem)
				{
					Particle->SetTemplate(Rows[i]->ParticleSystem);
					Particle->Activate(true);
				}
				else
					Particle->Deactivate();
			}

		}
		
	}
}

UParticleSystem* UElementsFunctionLibrary::GetParticleSystem(const UDataTable* Data, const EElements& OtherElement)
{
	if (Data != nullptr)
	{
		TArray< FElementParticleData const*> Rows;
		Data->GetAllRows("", Rows);

		for (uint32 i = 0; i < uint32(EElements::Max); i++)
		{
			if (Rows[i]->Element == OtherElement)
			{
				if (Rows[i]->ParticleSystem)
				{
					return Rows[i]->ParticleSystem;
					
				}
			}
		}
	}
	return nullptr;
}

//마우스를 아래로 내리면 false, 안움직이면 기존 element, 기존 데이터 없으면 false
bool UElementsFunctionLibrary::SelectElement(EElements& SelfElement, const FVector2D& MousePos)
{
	//Left = Fire, Up = Eletric, Right = Ice, Down = Cancle
	FVector2D Direction;
	float Distance;
	FVector2D Point(500, 500);

	(MousePos - Point).ToDirectionAndLength(Direction, Distance);

	if (Distance >= MinSelectDist)
	{
		bool Condition1 = Direction.X >= Direction.Y; // T = Right, Up
		bool Condition2 = Direction.X + Direction.Y >= 0; // T = Right, Down

		// Y < 0 이 Up


		if (Condition1 && Condition2) // Right
		{
			SelfElement = EElements::Ice;
			PreElementData = SelfElement;
			return true;
		}
		else if (Condition1 && !Condition2) // Up
		{
			SelfElement = EElements::Eletric;
			PreElementData = SelfElement;
			return true;
		}
		else if (!Condition1 && !Condition2) // Left
		{
			SelfElement = EElements::Fire;
			PreElementData = SelfElement;
			return true;
		}
		else if(!Condition1 && Condition2) // Down
		{
			return false;
		}
		
	}
	else if (PreElementData != EElements::None)
	{
		SelfElement = PreElementData;
		return true;
	}

	return false;

}
