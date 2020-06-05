// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileDamageTalent.h"

UProjectileDamageTalent::UProjectileDamageTalent()
{
	rank = 1;
	bLock = false;
	maxRank = 3;
	pointsToUnlock = 0;
	multipler = 2.f;
	Name = FText::FromString("Projectile Damage Increase");
}

float UProjectileDamageTalent::GetMultipler()
{
	return multipler;
}

void UProjectileDamageTalent::RankUp()
{
	Super::RankUp();
	rank;
	UE_LOG(LogTemp, Warning, TEXT("PistolDmg"));
	if (bLock == false)
	{
		multipler *= rank;
	}
}

void UProjectileDamageTalent::Unlock()
{
	if (rank < maxRank)
	{
		bLock = false;
	}
}

void UProjectileDamageTalent::Lock()
{
	Super::Lock();
}


