// Fill out your copyright notice in the Description page of Project Settings.


#include "ReloadTimeTalent.h"

UReloadTimeTalent::UReloadTimeTalent()
{
	maxRank = 3;
	bLock = true;
	pointsToUnlock = 4;
	rank = 1;
	ReloadTimeDecrease = 0;
	Name = FText::FromString("Reload Time Increase");
}

void UReloadTimeTalent::RankUp()
{
	Super::RankUp();
	if (bLock == false)
	{
		ReloadTimeDecrease += 0.75;
	}
}
