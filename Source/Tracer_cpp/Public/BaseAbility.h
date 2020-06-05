// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Engine/World.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseAbility.generated.h"

/**
 * 
 */
UCLASS()
class TRACER_CPP_API UBaseAbility : public UObject
{
	GENERATED_BODY()
	
public:
	float abilityCooldown;
	bool abilityFlag = true ;
	int abilityCharges;
	float abilityTime;
	bool abilitySpecialFlag = false;
	//TArray<FTransform> characterPositionArray;
	// Sets default values for this component's properties
	UBaseAbility();
	//UBaseAbility(float abilityCooldown);
	void setCooldown(float abilityCooldown);
	void setAbilityFlag(bool flag);
	virtual void UseAbility(class ACharacter* character);
	virtual void abilitySpecialEffect();

	UFUNCTION()
	virtual void setAbilityCooldown(float cooldown);
	UFUNCTION()
	virtual float getAbilityCooldown();
	UFUNCTION()
	FORCEINLINE bool getAbilitySpecialFlag() { return abilitySpecialFlag; }

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
		virtual void CooldownLogic(float time);

	UPROPERTY()
		class UCharacterAbilityManager* ParentAbilityManager;



protected:


};
