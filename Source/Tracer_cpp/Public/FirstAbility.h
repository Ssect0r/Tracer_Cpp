// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAbility.h"
#include "FirstAbility.generated.h"

/**
 * 
 */
UCLASS()
class TRACER_CPP_API UFirstAbility : public UBaseAbility
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFirstAbility();

	void AIUseAbility(ACharacter* character, FVector target);

	UFUNCTION()
	FORCEINLINE int GetFirstAbilityCharges() { return AbilityChargesActual; }


protected:
	virtual void UseAbility(ACharacter* character) override;


	

	
};
