// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/ActorComponent.h"
#include "CharacterAbilityManager.generated.h"

UENUM()
enum class EAbilityType : uint8
{
	PRIMARY,
	SECONDARY,
	ULTIMATE,
	MAX
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRACER_CPP_API UCharacterAbilityManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPROPERTY(VisibleAnywhere, Category = Gameplay)
	class UBaseAbility* FirstAbility;
	UPROPERTY(VisibleAnywhere, Category = Gameplay)
	class UBaseAbility* SecondAbility;
	UPROPERTY(VisibleAnywhere, Category = Gameplay)
	class UBaseAbility* UltimateAbility;

	float count = 0.f;
	bool flag = false;
	void setCharacter(ACharacter* character);
	ACharacter* character;

	UPROPERTY(VisibleAnywhere, Category = "Ability")
	float firstAbilityCooldownCounter;

	UPROPERTY(VisibleAnywhere, Category = "Ability")
	float FirstAbilityCooldown;

	UPROPERTY(VisibleAnywhere, Category = "Ability")
	float firstAbilityTime;

	UPROPERTY(VisibleAnywhere, Category = "Ability")
	int firstAbilityCharges;

	UPROPERTY(VisibleAnywhere, Category = "Ability")
	int firstAbilityChargesCounter;

	UPROPERTY(VisibleAnywhere, Category = "Ability")
	float secondAbilityCooldownCounter;

	UPROPERTY(VisibleAnywhere, Category = "Ability")
	float secondAbilityCooldown;

	UPROPERTY(VisibleAnywhere, Category = "Ability")
	bool bShouldRestart = false;

	UPROPERTY(VisibleAnywhere, Category = "Ability")
	float ultimateAbilityCooldownCounter;

	UPROPERTY(VisibleAnywhere, Category = "Ability")
	float ultimateAbilityCooldown;
	// Sets default values for this component's properties
	UCharacterAbilityManager();

	UFUNCTION()
	void UseAbility(EAbilityType AbilityType);

	//UFUNCTION()
	//void FirstAbilityCooldownLogic(float time, bool abilityFlag = true, int charges = 0);

	//UFUNCTION()
	//void SecondAbilityCooldownLogic(float time, bool abilityFlag = true , int charges = 0);

	//UFUNCTION()
	//void UltimateAbilityCooldownLogic(float time, bool abilityFlag = true, int charges = 0);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION()
	void lvlupFirstAbility(float decrease);
	UFUNCTION()
	void lvlupSecondAbility(float decrease);
	UFUNCTION()
	void lvlupUltimateAbility();
	UFUNCTION(BlueprintPure, Category = "Ability")
	int GetFirstAbilityCharges();
	UFUNCTION()
	void SetFirstAbilityCooldownCounter(float value);
	UFUNCTION()
	void SetUltimateSpecialFlagReady();
	UFUNCTION()
	bool bIsAbleToRestartDamageCounter();
	UFUNCTION()
	float GetFirstAbilityCooldownCounter();
	//UFUNCTION(BlueprintPure, Category = "Ability")
	//FORCEINLINE float GetFirstAbilityChargesCooldown() { return FirstAbilityCooldown - firstAbilityCooldownCounter; }
	UFUNCTION(BlueprintPure, Category = "Ability")
	float GetFirstAbilityChargesCooldown();
	UFUNCTION(BlueprintPure, Category = "Ability")
	float GetSecondAbilityCooldown();
	//UFUNCTION(BlueprintPure, Category = "Ability")
	//FORCEINLINE float GetUltimateAbilityCooldown() { return  ultimateAbilityCooldown - ultimateAbilityCooldownCounter; }
	UFUNCTION(BlueprintPure, Category = "Ability")
	float GetUltimateAbilityCooldown();
	UFUNCTION(BlueprintPure, Category = "Ability")
	FORCEINLINE UBaseAbility* GetFirstAbility() { return FirstAbility; }
	UFUNCTION(BlueprintPure, Category = "Ability")
	FORCEINLINE UBaseAbility* GetSecondAbility() { return SecondAbility; }
	UFUNCTION(BlueprintPure, Category = "Ability")
	bool GetSecondAbilityHealFlag();
	UFUNCTION()
	void SetSecondAbilityHealFlag(bool flag);
	UFUNCTION()
	float GetFirstAbilityCooldown();
	UFUNCTION()
	void SetFirstAbilityCooldown(float NewCooldown);
	UFUNCTION()
	void SetSecondAbilityCooldown(float NewCooldown);
	UFUNCTION(BlueprintPure, Category = "Ability")
	float GetSecondAbilityCooldownCounter();
	
};
