// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoCapacityTalent.h"

UAmmoCapacityTalent::UAmmoCapacityTalent()
{
	bLock = true;
	rank = 1;
	pointsToUnlock = 2;
	maxRank = 5;
	Name = FText::FromString("Ammo Capacity Increase");
	AmmoCapacityToIncrease = 0;
}

float UAmmoCapacityTalent::GetAmmoCapacityIncrease()
{
	return AmmoCapacityToIncrease;
}

void UAmmoCapacityTalent::RankUp()
{
	Super::RankUp();
	if (bLock == false)
	{
		AmmoCapacityToIncrease += 5;
	}
}
