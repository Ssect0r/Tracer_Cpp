// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FTalentSaveData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "DamageTalent")
		float ProjectileDamage = 8;

	UPROPERTY(EditAnywhere, Category = "DamageTalent")
		int ProjectileDamageTalentRank = 1;

	UPROPERTY(EditAnywhere, Category = "DamageTalent")
		bool ProjectileDamageTalentbLock = false;

	UPROPERTY(EditAnywhere, Category = "SpreadTalent")
		float GunSpread = 15.0f;

	UPROPERTY(EditAnywhere, Category = "SpreadTalent")
		int GunSpreadTalentRank = 1;

	UPROPERTY(EditAnywhere, Category = "SpreadTalent")
		bool GunSpreadTalentbLock = false;

	UPROPERTY(EditAnywhere, Category = "FireRateTalent")
		float FireRate = 0.25;

	UPROPERTY(EditAnywhere, Category = "FireRateTalent")
		int FireRateTalentRank = 1;

	UPROPERTY(EditAnywhere, Category = "FireRateTalent")
		bool FireRateTalentbLock = false;

	UPROPERTY(EditAnywhere, Category = "AmmoCapacityTalent")
		float AmmoCapacity = 30;

	UPROPERTY(EditAnywhere, Category = "AmmoCapacityTalent")
		int AmmoCapacityTalentRank = 1;

	UPROPERTY(EditAnywhere, Category = "AmmoCapacityTalent")
		bool AmmoCapacityTalentbLock = true;

	UPROPERTY(EditAnywhere, Category = "ReloadTimeTalent")
		float ReloadTime = 3;

	UPROPERTY(EditAnywhere, Category = "ReloadTimeTalent")
		int ReloadTimeTalentRank = 1;

	UPROPERTY(EditAnywhere, Category = "ReloadTimeTalent")
		bool ReloadTimeTalentbLock = true;

	UPROPERTY(EditAnywhere, Category = "AbilityCooldowns")
		float FirstAbilityCooldown = 6;

	UPROPERTY(EditAnywhere, Category = "AbilityCooldowns")
		float FirstAbilityCooldownCounter = FirstAbilityCooldown;

	UPROPERTY(EditAnywhere, Category = "AbilityCooldowns")
		int FirstAbilityCooldownTalentRank = 1;

	UPROPERTY(EditAnywhere, Category = "AbilityCooldowns")
		bool FirstAbilityCooldownTalentbLock = true;

	UPROPERTY(EditAnywhere, Category = "AbilityCooldowns")
		float SecondAbilityCooldown = 12;

	UPROPERTY(EditAnywhere, Category = "AbilityCooldowns")
		int SecondAbilityCooldownTalentRank = 1;

	UPROPERTY(EditAnywhere, Category = "AbilityCooldowns")
		bool SecondAbilityCooldownTalentbLock = false;

	UPROPERTY(EditAnywhere, Category = "Skillpoints")
		int SkillpointsSpended = 0;

	UPROPERTY(EditAnywhere, Category = "Game")
		int DamageToFinish = 50;

	UPROPERTY(EditAnywhere, Category = "Game")
		int KillsToFinish = 2;

	UPROPERTY(EditAnywhere, Category = "Game")
		FString ActualLevelToRestart;

	UPROPERTY(EditAnywhere, Category = "Game")
		int ActualLevelNumber = 1;

	UPROPERTY(EditAnywhere, Category = "Game")
		int SkillPointsToSpend = 1;
};

UCLASS(config = Game)
class TRACER_CPP_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FTalentSaveData BaseData;


	
	void SetTalentSaveData();
	
	void SetStartingValuesFromSaveData();

	void SetStartingValues();

	//UFUNCTION()
	//void SetKillsToFinish(int NewKillsToFinish);

	UFUNCTION()
		float GetSkillpointSpended();

	UFUNCTION()
		FString GetSActualLevelToRestart();

	UFUNCTION()
		int GetLevelNumber();
	
	UFUNCTION()
		void ResetLevelNumber();

	UFUNCTION()
		void SetKillsToEnd(int i);


	UFUNCTION()
		void SetActualLevelToRestart(FString LevelName);

};
