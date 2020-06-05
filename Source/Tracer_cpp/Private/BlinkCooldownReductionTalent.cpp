// Fill out your copyright notice in the Description page of Project Settings.


#include "BlinkCooldownReductionTalent.h"

UBlinkCooldownReductionTalent::UBlinkCooldownReductionTalent()
{
	maxRank = 3;
	pointsToUnlock = 5;
	bLock = true;
	rank = 1;
	BlinkCooldownReduction = 0;
	BlinkCooldownReductionPerLevel = 1;
	Name = FText::FromString("Blink Cooldown Reduction");
}

void UBlinkCooldownReductionTalent::RankUp()
{
	Super::RankUp();
	if (bLock == false)
	{
		BlinkCooldownReduction += BlinkCooldownReductionPerLevel;
	}
}
