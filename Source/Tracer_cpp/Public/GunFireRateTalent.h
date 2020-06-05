// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTalent.h"
#include "GunFireRateTalent.generated.h"

/**
 * 
 */
UCLASS()
class TRACER_CPP_API UGunFireRateTalent : public UBaseTalent
{
	GENERATED_BODY()

public:
	UGunFireRateTalent();

	UFUNCTION()
	float IncreaseFireRate();

protected:
	virtual void RankUp() override;


	float FireRateToAdd;
};
