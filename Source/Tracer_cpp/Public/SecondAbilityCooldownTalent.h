// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTalent.h"
#include "SecondAbilityCooldownTalent.generated.h"

/**
 * 
 */
UCLASS()
class TRACER_CPP_API USecondAbilityCooldownTalent : public UBaseTalent
{
	GENERATED_BODY()

public:
	USecondAbilityCooldownTalent();
	
	UPROPERTY(VisibleAnywhere, Category = "Talent")
	int SecondAbilityCooldownReductionPerLevel;

	UPROPERTY(VisibleAnywhere, Category = "Talent")
	int SecondAbilityCooldownDecrease;

	UFUNCTION()
	int GetSecondAbilityCooldownDecrease();
protected:
	virtual void RankUp() override;

};
