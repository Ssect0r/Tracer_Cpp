// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AIBaseAbility.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TRACER_CPP_API UAIBaseAbility : public UObject
{
	GENERATED_BODY()
	
public:
	UAIBaseAbility();
	UPROPERTY(EditAnywhere, Category = "AIAbility")
		FString AbilityName;

	UPROPERTY()
		FName Fname;

	UPROPERTY(EditAnywhere, Category = "AIAbility")
		float AbilityCooldown;

	UPROPERTY(EditAnywhere, Category = "AIAbility")
		float AbilityCooldownCounter;

	UPROPERTY(EditAnywhere, Category = "AIAbility")
		int AbilityCharges;

	UPROPERTY(EditAnywhere, Category = "AIAbility")
		int AbilityChargesActual;

	UPROPERTY(EditAnywhere, Category = "AIAbility")
		bool bIsOnCD;

	UPROPERTY(EditAnywhere, Category = "AIAbility")
		bool bHasCharges;

	UFUNCTION()
		virtual void UseAbility(class ACharacter* character);

	UFUNCTION()
		virtual void CooldownLogic(float time);

	UFUNCTION()
		FORCEINLINE bool GetbIsOnCD() {	return bIsOnCD; }

	UFUNCTION()
		FORCEINLINE int GetAbilityCharges() { return AbilityCharges; }

	UFUNCTION()
		FORCEINLINE int GetAbilityChargesActual() { return AbilityChargesActual; }

	UFUNCTION()
		FORCEINLINE FName GetAbilityFName() { return Fname; }

	UPROPERTY()
	class UAIAbilityManager* ParentAbilityManager;
};
