// Fill out your copyright notice in the Description page of Project Settings.


#include "AIRotatingOrbAbility.h"
#include "RotatingOrb.h"
#include "AIAbilityManager.h"

UAIRotatingOrbAbility::UAIRotatingOrbAbility()
{
	AbilityCooldown = 0.f;
}

void UAIRotatingOrbAbility::UseAbility(ACharacter* character)
{
	//RotatingClass;
	//ARotatingOrb* Orb = Cast<ARotatingOrb>(RotatingClass);
	//if (Orb)
	//{
	//	Orb->SetHost(character);
	//
	if (ParentAbilityManager)
	{
		for (TSubclassOf<class AActor> RotatingClass : OrbsArray) {
			AActor* curSpawn = ParentAbilityManager->SpawnOrb(RotatingClass);
			if (curSpawn)
			{
				//curSpawn->AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
				curSpawn->SetOwner(character);
				
			}
		}
		bIsOnCD = true;
	}
}
//	}
//}
