// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTalent.h"

void UBaseTalent::RankUp()
{
	if (rank < maxRank)
	{
		rank++;
		
	}
	else
	{
		Lock();
	}
}

void UBaseTalent::Unlock()
{
	bLock = false;
}

void UBaseTalent::Lock()
{
	bLock = true;
}

int UBaseTalent::GetActualRank()
{
	return rank;
}

int UBaseTalent::GetMaxRank()
{
	return maxRank;
}

int UBaseTalent::GetPointsToUnlock()
{
	return pointsToUnlock;
}
