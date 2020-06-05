// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIGuard.h"
#include "MageAI.generated.h"

/**
 * 
 */
UCLASS()
class TRACER_CPP_API AMageAI : public AAIGuard
{
	GENERATED_BODY()

		AMageAI();

	UPROPERTY(EditAnywhere, Category = "AbilityManager")
	class UAIAbilityManager* AbilityManager;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		float RangeToBlink;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		float RangeToFireball;

	virtual void Tick(float DeltaTime) override;
	void OnPawnSeen(APawn* SeenPawn) override;
	void OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume) override;

protected:
	virtual void BeginPlay() override;
	
};
