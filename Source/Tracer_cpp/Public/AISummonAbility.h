// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIBaseAbility.h"
#include "AISummonAbility.generated.h"

/**
 * 
 */
UCLASS()
class TRACER_CPP_API UAISummonAbility : public UAIBaseAbility
{
	GENERATED_BODY()

public:
	UAISummonAbility();

	UPROPERTY(EditAnywhere, Category = "AI")
		TSubclassOf<class APawn> SummonClass;

	
	virtual void UseAbility(ACharacter* character) override;

	
};
