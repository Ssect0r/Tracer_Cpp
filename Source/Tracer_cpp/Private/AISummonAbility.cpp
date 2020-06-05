// Fill out your copyright notice in the Description page of Project Settings.


#include "AISummonAbility.h"
#include "TrackerBot.h"
#include "AIGuard.h"
#include "Engine\World.h"
#include "AIAbilityManager.h"

UAISummonAbility::UAISummonAbility()
{
	AbilityCooldown = 5.f;
	AbilityCharges = 3;
	bIsOnCD = false;
	bHasCharges = true;
	AbilityName = "SummonAbility";
	Fname = (*AbilityName);
}

void UAISummonAbility::UseAbility(ACharacter* character)
{
	if (!bIsOnCD)
	{
		if (ParentAbilityManager)
		{
			APawn* curSpawn = ParentAbilityManager->SpawnEnemy(SummonClass);
			if (curSpawn)
			{
				//curSpawn->AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
				curSpawn->SetOwner(character);
				curSpawn->SpawnDefaultController();
				bIsOnCD = true;
			}
		}
	}
}
