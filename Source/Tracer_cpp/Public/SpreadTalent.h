// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTalent.h"
#include "SpreadTalent.generated.h"

/**
 * 
 */
UCLASS()
class TRACER_CPP_API USpreadTalent : public UBaseTalent
{
	GENERATED_BODY()

public:
	USpreadTalent();

	float SpreadDecrease;

	UFUNCTION()
	float GetNewSpread();

protected:
	virtual void RankUp() override;
	//virtual void Unlock() override;
	//virtual void Lock() override;
};
