// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Engine/World.h"
#include "Tracer_cppCharacter.h"
#include "GameFramework/PlayerController.h"
#include "CharacterTalentTree.h"
#include "CharacterAbilityManager.h"

void UMyGameInstance::SetTalentSaveData()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	ATracer_cppCharacter* Pawn = nullptr;
	if (PC)
	{
		Pawn = Cast<ATracer_cppCharacter>(PC->GetPawn());
		if (Pawn)
		{
			UCharacterTalentTree* TalentTree = Pawn->GetTalentTree();
			if (TalentTree)
			{
				BaseData.AmmoCapacity = Pawn->AmmoCapacity;
				BaseData.AmmoCapacityTalentRank = Pawn->GetTalentTree()->GetAmmoCapacityTalentRank();
				BaseData.AmmoCapacityTalentbLock = Pawn->GetTalentTree()->GetAmmoCapacityTalentbLock();

				BaseData.FireRate = Pawn->rateOfFire;
				BaseData.FireRateTalentRank = Pawn->GetTalentTree()->GetFireRateTalentRank();
				BaseData.FireRateTalentbLock = Pawn->GetTalentTree()->GetFireRateTalentTalentbLock();

				BaseData.GunSpread = Pawn->BulletSpread;
				BaseData.GunSpreadTalentRank = Pawn->GetTalentTree()->GetSpreadTalentRank();
				BaseData.GunSpreadTalentbLock = Pawn->GetTalentTree()->GetSpreadTalentTalentbLock();

				BaseData.ProjectileDamage = Pawn->PlayerPistolDamage;
				BaseData.ProjectileDamageTalentRank = Pawn->GetTalentTree()->GetProjectileDamageTalentRank();
				BaseData.ProjectileDamageTalentbLock = Pawn->GetTalentTree()->GetProjectileDamageTalentbLock();

				BaseData.ReloadTime = Pawn->ReloadTime;
				BaseData.ReloadTimeTalentRank = Pawn->GetTalentTree()->GetReloadTimeTalentRank();
				BaseData.ReloadTimeTalentbLock = Pawn->GetTalentTree()->GetReloadTimeTalentbLock();

				BaseData.FirstAbilityCooldown = Pawn->GetAbilityManager()->GetFirstAbilityCooldown();
				//BaseData.FirstAbilityCooldownCounter = Pawn->GetAbilityManager()->GetFirstAbilityCooldownCounter();
				BaseData.FirstAbilityCooldownTalentRank = Pawn->GetTalentTree()->GetBlinkCooldownTalentRank();
				BaseData.FirstAbilityCooldownTalentbLock = Pawn->GetTalentTree()->GetBlinkCooldownTalentbLock();

				BaseData.SecondAbilityCooldown = Pawn->GetAbilityManager()->GetSecondAbilityCooldown(); //
				BaseData.SecondAbilityCooldownTalentRank = Pawn->GetTalentTree()->GetRewindCooldownTalentRank();
				BaseData.SecondAbilityCooldownTalentbLock = Pawn->GetTalentTree()->GetRewindCooldownTalentbLock();

				BaseData.SkillpointsSpended = Pawn->GetSkillpointSpended();
				BaseData.DamageToFinish += 150;
				BaseData.KillsToFinish += 3;
				BaseData.ActualLevelNumber += 1;
				BaseData.SkillPointsToSpend = Pawn->GetSkillPointToSpend() + 1;
			}
		}
	}
}

void UMyGameInstance::SetStartingValuesFromSaveData()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	ATracer_cppCharacter* Pawn = nullptr;
	if (PC)
	{
		Pawn = Cast<ATracer_cppCharacter>(PC->GetPawn());
		if (Pawn)
		{
			UCharacterTalentTree* TalentTree = Pawn->GetTalentTree();
			if (TalentTree)
			{
				Pawn->PlayerPistolDamage = BaseData.ProjectileDamage;
				Pawn->GetTalentTree()->SetProjectileDamageTalent(BaseData.ProjectileDamageTalentRank, BaseData.ProjectileDamageTalentbLock);

				Pawn->AmmoCapacity = BaseData.AmmoCapacity;
				Pawn->GetTalentTree()->SetAmmoCapacityTalent(BaseData.AmmoCapacityTalentRank, BaseData.AmmoCapacityTalentbLock);

				Pawn->rateOfFire = BaseData.FireRate;
				Pawn->GetTalentTree()->SetFireRateTalent(BaseData.FireRateTalentRank, BaseData.FireRateTalentbLock);

				Pawn->BulletSpread = BaseData.GunSpread;
				Pawn->GetTalentTree()->SetSpreadTalent(BaseData.GunSpreadTalentRank, BaseData.GunSpreadTalentbLock);

				Pawn->ReloadTime = BaseData.ReloadTime;
				Pawn->GetTalentTree()->SetReloadTimeTalent(BaseData.ReloadTimeTalentRank, BaseData.ReloadTimeTalentbLock);

				Pawn->GetAbilityManager()->SetFirstAbilityCooldown(BaseData.FirstAbilityCooldown);
				//Pawn->GetAbilityManager()->SetFirstAbilityCooldownCounter(BaseData.FirstAbilityCooldown);
				Pawn->GetTalentTree()->SetBlinkCooldownTalent(BaseData.FirstAbilityCooldownTalentRank, BaseData.FirstAbilityCooldownTalentbLock);

				Pawn->GetAbilityManager()->SetSecondAbilityCooldown(BaseData.SecondAbilityCooldown);
				Pawn->GetTalentTree()->SetRewindCooldownTalent(BaseData.SecondAbilityCooldownTalentRank, BaseData.SecondAbilityCooldownTalentbLock);

				Pawn->GetTalentTree()->SkillPointsSpended = BaseData.SkillpointsSpended;
				Pawn->SetDamageToFinishLevel(BaseData.DamageToFinish);
				Pawn->SetKillsToFinishLevel(BaseData.KillsToFinish);
				Pawn->SetSkillPointToSpend(BaseData.SkillPointsToSpend);
			}
		}
	}
}

void UMyGameInstance::SetStartingValues()
{
		BaseData.ProjectileDamage = 8;
		BaseData.ProjectileDamageTalentRank = 1;
		BaseData.ProjectileDamageTalentbLock = false;
		BaseData.GunSpread = 15.0f;
		BaseData.GunSpreadTalentRank = 1;
		BaseData.GunSpreadTalentbLock = false;
		BaseData.FireRate = 0.25;
		BaseData.FireRateTalentRank = 1;
		BaseData.FireRateTalentbLock = false;
		BaseData.AmmoCapacity = 30;
		BaseData.AmmoCapacityTalentRank = 1;
		BaseData.AmmoCapacityTalentbLock = true;
		BaseData.ReloadTime = 3;
		BaseData.ReloadTimeTalentRank = 1;
		BaseData.ReloadTimeTalentbLock = true;
		BaseData.FirstAbilityCooldown = 6;
		BaseData.FirstAbilityCooldownCounter = BaseData.FirstAbilityCooldown;
		BaseData.FirstAbilityCooldownTalentRank = 1;
		BaseData.FirstAbilityCooldownTalentbLock = true;
		BaseData.SecondAbilityCooldown = 12;
		BaseData.SecondAbilityCooldownTalentRank = 1;
		BaseData.SecondAbilityCooldownTalentbLock = false;
		BaseData.SkillpointsSpended = 0;
		BaseData.DamageToFinish = 50;
		BaseData.KillsToFinish = 2;
		BaseData.ActualLevelToRestart;
		BaseData.ActualLevelNumber = 1;
		BaseData.SkillPointsToSpend = 1;
		SetStartingValuesFromSaveData();
}

float UMyGameInstance::GetSkillpointSpended()
{
	return BaseData.SkillpointsSpended;
}

FString UMyGameInstance::GetSActualLevelToRestart()
{
	return BaseData.ActualLevelToRestart;
}

int UMyGameInstance::GetLevelNumber()
{
	return BaseData.ActualLevelNumber;
}

void UMyGameInstance::ResetLevelNumber()
{
	BaseData.ActualLevelNumber = 0;
}

void UMyGameInstance::SetKillsToEnd(int i)
{
	BaseData.KillsToFinish = i;
}

void UMyGameInstance::SetActualLevelToRestart(FString LevelName)
{
	BaseData.ActualLevelToRestart = LevelName;
}

