// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterTalentTree.h"
#include "ProjectileDamageTalent.h"
#include "GunFireRateTalent.h"
#include "SpreadTalent.h"
#include "ReloadTimeTalent.h"
#include "AmmoCapacityTalent.h"
#include "BlinkCooldownReductionTalent.h"
#include "SecondAbilityCooldownTalent.h"


UCharacterTalentTree::UCharacterTalentTree()
{
	SkillPoints = 0;
	SkillPointsSpended = 0;
	//ProjectileDamageTalent1 = NewObject<UProjectileDamageTalent>(this, UProjectileDamageTalent::StaticClass());
	//ProjectileDamageTalent1 = CreateDefaultSubobject<UProjectileDamageTalent>(TEXT("ProjectileDamageTalent"));

}

void UCharacterTalentTree::BeginPlay()
{
	ProjectileDamageTalent1 = NewObject<UProjectileDamageTalent>(this, UProjectileDamageTalent::StaticClass());
	FireRateTalent = NewObject<UGunFireRateTalent>(this, UGunFireRateTalent::StaticClass());
	WeaponSpreadTalent = NewObject<USpreadTalent> (this, USpreadTalent::StaticClass());
	ReloadTimeTalent = NewObject<UReloadTimeTalent>(this, UReloadTimeTalent::StaticClass());
	AmmoCapacityTalent = NewObject<UAmmoCapacityTalent>(this, UAmmoCapacityTalent::StaticClass());
	BlinkCooldownReductionTalent = NewObject<UBlinkCooldownReductionTalent>(this, UBlinkCooldownReductionTalent::StaticClass());
	SecondAbilityCooldownTalent = NewObject<USecondAbilityCooldownTalent>(this, USecondAbilityCooldownTalent::StaticClass());
	TalentArray.Add(ProjectileDamageTalent1);
	TalentArray.Add(FireRateTalent);
	TalentArray.Add(WeaponSpreadTalent);
	TalentArray.Add(ReloadTimeTalent);
	TalentArray.Add(AmmoCapacityTalent);
	TalentArray.Add(BlinkCooldownReductionTalent);
	TalentArray.Add(SecondAbilityCooldownTalent);
	TalentsUnderChange = false;
}

void UCharacterTalentTree::GainSkillPoint()
{
	SkillPoints++;
}

bool UCharacterTalentTree::SpendSkillPoint()
{
	if (SkillPoints > 0)
	{
		SkillPointsSpended++;
		SkillPoints--;
		UE_LOG(LogTemp, Warning, TEXT("SkillPointsSpended: %d"), SkillPointsSpended);
		return true;
	}
	else
	{
		return false;
	}
}

float UCharacterTalentTree::GetProjectileDamage()
{
	//first you should look through array of talents if there is a projectile damage talent
	//for loop that goes through the array talents
	//if(Array[i]->GetClass() == UProjectileDamageTalent::StaticClass())
	//Cast<UProjectileDamageTalent>(Array[i])
	UProjectileDamageTalent* projectileDamageTalent = Cast<UProjectileDamageTalent>(LookForTalentInArray(UProjectileDamageTalent::StaticClass()));
	if (projectileDamageTalent)
	{
		return projectileDamageTalent->GetMultipler();
	}
	else
	{
		return 1.f;
	}

	//then if there is, you should read the current multipliers

	//if not multiplier should be 1
	//return ProjectileDamageTalent1->GetMultipler();
}

float UCharacterTalentTree::GetFireRate()
{
	UGunFireRateTalent* fireRateTalent = Cast<UGunFireRateTalent>(LookForTalentInArray(UGunFireRateTalent::StaticClass()));
	if (fireRateTalent)
	{
		return fireRateTalent->IncreaseFireRate();
	}
	else
	{
		return 0.0f;
	}

}

float UCharacterTalentTree::GetWeaponSpreadDecrease()
{
	USpreadTalent* SpreadTalent = Cast<USpreadTalent>(LookForTalentInArray(USpreadTalent::StaticClass()));
	if (SpreadTalent)
	{
		return SpreadTalent->GetNewSpread();
	}
	else
	{
		return 0.0f;
	}
}

float UCharacterTalentTree::GetReloadTimeDecrease()
{
	UReloadTimeTalent* ReloadTalent = Cast<UReloadTimeTalent>(LookForTalentInArray(UReloadTimeTalent::StaticClass()));
	if (ReloadTalent)
	{
		return ReloadTalent->GetReloadTimeDecrease();
	}
	else
	{
		return 0.0f;
	}
}

float UCharacterTalentTree::GetAmmoCapacityIncrease()
{
	UAmmoCapacityTalent* AmmoCapacityTalent = Cast<UAmmoCapacityTalent>(LookForTalentInArray(UAmmoCapacityTalent::StaticClass()));
	if (AmmoCapacityTalent)
	{
		return AmmoCapacityTalent->GetAmmoCapacityIncrease();
	}
	else
	{
		return 0.0f;
	}
}

float UCharacterTalentTree::GetBlinkCooldownReduction()
{
	UBlinkCooldownReductionTalent* BlinkCooldownReductionTalent = Cast<UBlinkCooldownReductionTalent>(LookForTalentInArray(UBlinkCooldownReductionTalent::StaticClass()));
	if (BlinkCooldownReductionTalent)
	{
		return BlinkCooldownReductionTalent->GetBlinkCooldownReduction();
	}
	else
	{
		return 0.0f;
	}
}

float UCharacterTalentTree::GetSecondAbilityCooldownReduction()
{
	USecondAbilityCooldownTalent* SecondAbilityCooldownReductionTalent = Cast<USecondAbilityCooldownTalent>(LookForTalentInArray(USecondAbilityCooldownTalent::StaticClass()));
	if (SecondAbilityCooldownReductionTalent)
	{
		return SecondAbilityCooldownReductionTalent->GetSecondAbilityCooldownDecrease();
	}
	else
	{
		return 0.0f;
	}
}

int UCharacterTalentTree::CheckTalentClass(UBaseTalent* ClassType)
{

	int TalentType = 0;
	if (ClassType->IsA(UProjectileDamageTalent::StaticClass()))
	{
		if(ProjectileDamageTalent1->bLock == false)
		TalentType = 1;
	}
	if (ClassType->IsA(UGunFireRateTalent::StaticClass()))
	{
		if (FireRateTalent->bLock == false)
		TalentType = 2;
	}
	if (ClassType->IsA(USpreadTalent::StaticClass()))
	{
		if (WeaponSpreadTalent->bLock == false)
		TalentType = 3;
	}
	if (ClassType->IsA(UReloadTimeTalent::StaticClass()))
	{
		if (ReloadTimeTalent->bLock == false)
		TalentType = 4;
	}
	if (ClassType->IsA(UAmmoCapacityTalent::StaticClass()))
	{
		if (AmmoCapacityTalent->bLock == false)
		TalentType = 5;
	}
	if (ClassType->IsA(UBlinkCooldownReductionTalent::StaticClass()))
	{
		if (BlinkCooldownReductionTalent->bLock == false)
		TalentType = 6;
	}
	if (ClassType->IsA(USecondAbilityCooldownTalent::StaticClass()))
	{
		if (SecondAbilityCooldownTalent->bLock == false)
		TalentType = 7;
	}
		RefreshTalents();
		return TalentType;
	
}

int UCharacterTalentTree::GetSkillPointsSpended()
{
	return SkillPoints;
}

int UCharacterTalentTree::GetProjectileDamageTalentRank()
{
	int rank = ProjectileDamageTalent1->GetActualRank();
	return rank;
}

bool UCharacterTalentTree::GetProjectileDamageTalentbLock()
{
	bool bLock = ProjectileDamageTalent1->bLock;
	return bLock;
}

int UCharacterTalentTree::GetFireRateTalentRank()
{
	int rank = FireRateTalent->GetActualRank();
	return rank;
}

bool UCharacterTalentTree::GetFireRateTalentTalentbLock()
{
	bool bLock = FireRateTalent->bLock;
	return bLock;
}

int UCharacterTalentTree::GetSpreadTalentRank()
{
	int rank = WeaponSpreadTalent->GetActualRank();
	return rank;
}

bool UCharacterTalentTree::GetSpreadTalentTalentbLock()
{
	bool bLock = WeaponSpreadTalent->GetbLock();
	return bLock;
}

int UCharacterTalentTree::GetReloadTimeTalentRank()
{
	int rank = ReloadTimeTalent->GetActualRank();
	return rank;
}

bool UCharacterTalentTree::GetReloadTimeTalentbLock()
{
	bool bLock = ReloadTimeTalent->GetbLock();
	return bLock;
}

int UCharacterTalentTree::GetAmmoCapacityTalentRank()
{
	int rank = AmmoCapacityTalent->GetActualRank();
	return rank;
}

bool UCharacterTalentTree::GetAmmoCapacityTalentbLock()
{
	bool bLock = AmmoCapacityTalent->bLock;
	return bLock;
}

int UCharacterTalentTree::GetBlinkCooldownTalentRank()
{
	int rank = BlinkCooldownReductionTalent->GetActualRank();
	return rank;
}

bool UCharacterTalentTree::GetBlinkCooldownTalentbLock()
{
	bool bLock = BlinkCooldownReductionTalent->GetbLock();
	return bLock;
}

int UCharacterTalentTree::GetRewindCooldownTalentRank()
{
	int rank = SecondAbilityCooldownTalent->GetActualRank();
	return rank;
}

bool UCharacterTalentTree::GetRewindCooldownTalentbLock()
{
	bool bLock = SecondAbilityCooldownTalent->GetbLock();
	return bLock;
}

void UCharacterTalentTree::SetProjectileDamageTalent(int rank, bool bLock)
{
	ProjectileDamageTalent1->rank = rank;
	ProjectileDamageTalent1->bLock = bLock;
}

void UCharacterTalentTree::SetFireRateTalent(float rank, bool bLock)
{
	FireRateTalent->rank = rank;
	FireRateTalent->bLock = bLock;
}

void UCharacterTalentTree::SetSpreadTalent(float rank, bool bLock)
{
	WeaponSpreadTalent->rank = rank;
	WeaponSpreadTalent->bLock = bLock;
}

void UCharacterTalentTree::SetReloadTimeTalent(float rank, bool bLock)
{
	ReloadTimeTalent->rank = rank;
	ReloadTimeTalent->bLock = bLock;
}

void UCharacterTalentTree::SetAmmoCapacityTalent(float rank, bool bLock)
{
	AmmoCapacityTalent->rank = rank;
	AmmoCapacityTalent->bLock = bLock;
}

void UCharacterTalentTree::SetBlinkCooldownTalent(float rank, bool bLock)
{
	BlinkCooldownReductionTalent->rank = rank;
	BlinkCooldownReductionTalent->bLock = bLock;
}

void UCharacterTalentTree::SetRewindCooldownTalent(float rank, bool bLock)
{
	SecondAbilityCooldownTalent->rank = rank;
	SecondAbilityCooldownTalent->bLock = bLock;
}


// ZAMIENIC
//void UCharacterTalentTree::SetTalentCooldown(UBaseTalent* talent, float rank, bool bLock)
//{
//	if (talent)
//	{
//		talent->rank = rank;
//		talent->bLock = bLock;
//	}
//}



UBaseTalent* UCharacterTalentTree::LookForTalentInArray(UClass* ClassParameter)
{
	UBaseTalent* foundObject = nullptr;
	for (UBaseTalent* Uclass : TalentArray)
	{
		if (Uclass->IsA(ClassParameter))
		{
			foundObject = Uclass;
		}
	}
	return foundObject;
}

void UCharacterTalentTree::RefreshTalents()
{
	//TalentsUnderChange = true;
	for (UBaseTalent* Uclass : TalentArray)
	{
		if (Uclass->GetbLock() == true && Uclass->pointsToUnlock <= SkillPointsSpended)
		{
			Uclass->bLock = false;
		}
			if (Uclass->GetbLock() == false && Uclass->rank == Uclass->GetMaxRank())
		{
			Uclass->bLock = true;
		}
	}
}

bool UCharacterTalentTree::CheckSkillPoints()
{
	if (SkillPoints > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}


