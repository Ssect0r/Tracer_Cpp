// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTalent.h"
#include "AmmoCapacityTalent.generated.h"

/**
 * 
 */
UCLASS()
class TRACER_CPP_API UAmmoCapacityTalent : public UBaseTalent
{
	GENERATED_BODY()

public:
	UAmmoCapacityTalent();

	float GetAmmoCapacityIncrease();

protected:
	virtual void RankUp() override;

	float AmmoCapacityToIncrease;
};
