// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CHumanoidCharacter.h"
#include "Interface/AIActionInterface.h"
#include "CHumanoidEnemy.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class POTOPOLIO_CPP_2305_API ACHumanoidEnemy : public ACHumanoidCharacter,
	public IAIActionInterface
{
	GENERATED_BODY()
	
public:
	ACHumanoidEnemy();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;

	// ªÁ∏¡Ω√ Trigger »£√‚
protected:
	UFUNCTION()
		void OnPerceptionUpdated(const TArray<AActor*>& OutActors);
	UFUNCTION()
		void DestroyedEvent(AActor* DestroyedActor);

	virtual void HitUpdateFunction() override;

private:
	void AIActionA() override;
	void AIActionB() override;
	void AIAction1() override;
	void AIAction2() override;
	void AIAction3() override;
	void AIAction4() override;

	void AIAddTarget(ACCharacter* Character, ACBaseTrigger* Trigger) override;

protected:
	UPROPERTY(EditDefaultsOnly)
		class UAIPerceptionComponent* AIPerception;
	UPROPERTY(VisibleDefaultsOnly)
		class UAISenseConfig_Sight* SightSense;
	UPROPERTY(BlueprintReadOnly)
		class ACPlayer* Target;
	UPROPERTY(EditDefaultsOnly)
		class UBehaviorTree* AIBehaviorTree;
	UPROPERTY(EditDefaultsOnly)
		class UWidgetComponent* Widget;

	class ACBaseTrigger* DeadEventTrigger;
};
