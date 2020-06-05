// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBaseAbility.h"

UAIBaseAbility::UAIBaseAbility()
{
	bIsOnCD = false;
	AbilityCharges = 0;
	AbilityCooldown = 0.f;
	AbilityCooldownCounter = 0.f;
	bHasCharges = false;
}

void UAIBaseAbility::UseAbility(ACharacter* character)
{
}

void UAIBaseAbility::CooldownLogic(float time)
{
	if (bIsOnCD)
	{
		if (bHasCharges)
		{
			if (AbilityChargesActual < AbilityCharges)
			{
				if (AbilityCooldownCounter <= AbilityCooldown)
				{
					AbilityCooldownCounter += time;
				}
				else
				{
 					AbilityChargesActual++;
					AbilityCooldownCounter = 0;
				}
			}
		}
		else if (!bHasCharges && AbilityCooldownCounter < AbilityCooldown)
		{
			AbilityCooldownCounter += time;
		}
		else
		{
			AbilityCooldownCounter = 0;
		    bIsOnCD = false;
		}
	}
}
