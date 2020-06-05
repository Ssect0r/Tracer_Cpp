// Fill out your copyright notice in the Description page of Project Settings.


#include "SpreadTalent.h"


USpreadTalent::USpreadTalent()
{
	maxRank = 4;
	rank = 1;
	bLock = true;
	pointsToUnlock = 2;
	Name = FText::FromString("Weapon Spread Decrease");
	SpreadDecrease = 0;
}

float USpreadTalent::GetNewSpread()
{
	return SpreadDecrease;
}

void USpreadTalent::RankUp()
{
	Super::RankUp();
	if (bLock == false)
	{
		SpreadDecrease += 3;
	}
}
