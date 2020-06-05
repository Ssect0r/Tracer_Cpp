// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTalent.h"
#include "ProjectileDamageTalent.generated.h"

/**
 * 
 */
UCLASS()
class TRACER_CPP_API UProjectileDamageTalent : public UBaseTalent
{
	GENERATED_BODY()
public:
	UProjectileDamageTalent();

	UFUNCTION()
	float GetMultipler();

	virtual void RankUp() override;
	virtual void Unlock() override;
	virtual void Lock();

protected:
	float multipler;
};
