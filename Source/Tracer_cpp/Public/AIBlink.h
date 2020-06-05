// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIBaseAbility.h"
#include "AIBlink.generated.h"

/**
 * 
 */
UCLASS()
class TRACER_CPP_API UAIBlink : public UAIBaseAbility
{
	GENERATED_BODY()

		UAIBlink();
public:	
	UPROPERTY()
		APawn* Target;

		UPROPERTY(EditDefaultsOnly, Category = "Blink")
		UParticleSystem* BlinkEffect;


		UFUNCTION()
		void SetTarget(APawn* targetPawn);

		virtual void UseAbility(ACharacter* character) override;
	
};
