// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIGuard.h"
#include "AIBoss.generated.h"

/**
 * 
 */
UCLASS()
class TRACER_CPP_API AAIBoss : public AAIGuard
{

	GENERATED_BODY()

	AAIBoss();

	UPROPERTY(EditAnywhere, Category = "AbilityManager")
	class UAIAbilityManager* AbilityManager;


	virtual void Tick(float DeltaTime) override;
	void OnPawnSeen(APawn* SeenPawn) override;
	void OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume) override;

protected:
	virtual void BeginPlay() override;
};
