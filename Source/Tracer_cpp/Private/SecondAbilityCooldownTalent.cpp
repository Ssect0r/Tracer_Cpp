// Fill out your copyright notice in the Description page of Project Settings.


#include "SecondAbilityCooldownTalent.h"

USecondAbilityCooldownTalent::USecondAbilityCooldownTalent()
{
	maxRank = 3;
	pointsToUnlock = 0;
	bLock = false;
	rank = 1;
	SecondAbilityCooldownReductionPerLevel = 1;
	Name = FText::FromString("Rewind Cooldown Reduction");
}

int USecondAbilityCooldownTalent::GetSecondAbilityCooldownDecrease()
{
	return SecondAbilityCooldownDecrease;
}

void USecondAbilityCooldownTalent::RankUp()
{
	Super::RankUp();
	if (bLock == false)
	{
		SecondAbilityCooldownDecrease += SecondAbilityCooldownReductionPerLevel;
	}
}
