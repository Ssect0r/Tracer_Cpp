// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIBaseAbility.h"
#include "AIRotatingOrbAbility.generated.h"

/**
 * 
 */
UCLASS()
class TRACER_CPP_API UAIRotatingOrbAbility : public UAIBaseAbility
{
	GENERATED_BODY()

	UAIRotatingOrbAbility();
	UPROPERTY(EditAnywhere, Category = "AI")
	TArray<TSubclassOf<class AActor>> OrbsArray;


	virtual void UseAbility(ACharacter* character) override;
	
};
