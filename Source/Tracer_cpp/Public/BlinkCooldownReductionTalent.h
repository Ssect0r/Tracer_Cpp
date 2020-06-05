// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTalent.h"
#include "BlinkCooldownReductionTalent.generated.h"

/**
 * 
 */
UCLASS()
class TRACER_CPP_API UBlinkCooldownReductionTalent : public UBaseTalent
{
	GENERATED_BODY()

public:
	UBlinkCooldownReductionTalent();

	UFUNCTION()
	FORCEINLINE float GetBlinkCooldownReduction() { return BlinkCooldownReduction; }

	UPROPERTY(EditAnywhere, Category = "Talent")
	float BlinkCooldownReductionPerLevel = 1.f;

protected:
	virtual void RankUp() override;
	float BlinkCooldownReduction;


};
