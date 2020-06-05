// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAbility.h"
#include "UltimateAbility.generated.h"

/**
 * 
 */
UCLASS()
class TRACER_CPP_API UUltimateAbility : public UBaseAbility
{
	GENERATED_BODY()	
public:
	// Sets default values for this component's properties
	UUltimateAbility();
	bool bRestartDamageCounter = false;
	

protected:
	virtual void UseAbility(ACharacter* character) override;


};
