// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAbility.h"
#include "SecondAbility.generated.h"

/**
 * 
 */
UCLASS()
class TRACER_CPP_API USecondAbility : public UBaseAbility
{
	GENERATED_BODY()
	
public:
	// Sets default values for this component's properties
	USecondAbility();
	UPROPERTY()
	bool HealFlag = false;

	UPROPERTY()
	float AbilityTimeCounter;

	UPROPERTY()
	TArray<FTransform> CharacterPositionArray;

	UPROPERTY()
	float AbilityTime = 3.f;

	UFUNCTION()
	FORCEINLINE bool GetHealFlag() { return HealFlag;  }

	UFUNCTION()
	void SetHealFlag(bool flag);


	virtual void CooldownLogic(float time) override;

protected:
	virtual void UseAbility(ACharacter* character) override;


};
