// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTalent.h"
#include "ReloadTimeTalent.generated.h"

/**
 * 
 */
UCLASS()
class TRACER_CPP_API UReloadTimeTalent : public UBaseTalent
{
	GENERATED_BODY()
	
public:
	UReloadTimeTalent();
	
	float ReloadTimeDecrease;

	UFUNCTION()
	FORCEINLINE float GetReloadTimeDecrease() { return ReloadTimeDecrease; }

protected:
	virtual void RankUp() override;
};
