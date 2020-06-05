// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIGuard.h"
#include "SummonerAI.generated.h"

/**
 * 
 */
UCLASS()
class TRACER_CPP_API ASummonerAI : public AAIGuard
{
	GENERATED_BODY()
public:
	ASummonerAI();

	UPROPERTY(EditAnywhere, Category = "AbilityManager")
	class UAIAbilityManager* AbilityManager;


	virtual void Tick(float DeltaTime) override;
	void OnPawnSeen(APawn* SeenPawn) override;
    void OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume) override;
protected:
	virtual void BeginPlay() override;
};
