// Fill out your copyright notice in the Description page of Project Settings.


#include "GunFireRateTalent.h"

UGunFireRateTalent::UGunFireRateTalent()
{
	pointsToUnlock = 3;
	bLock = true;
	rank = 1;
	FireRateToAdd = 0.6;
	Name = FText::FromString("Fire Rate Increase");
	maxRank = 3;
}

float UGunFireRateTalent::IncreaseFireRate()
{
	return FireRateToAdd;
}

void UGunFireRateTalent::RankUp()
{
	UE_LOG(LogTemp, Warning, TEXT("FireRate: %f"),FireRateToAdd);
	Super::RankUp();
	if(bLock == false)
	{
		float rankInFloat = float(rank);
		FireRateToAdd -= (rankInFloat / 10);
	}
}

