// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAbility.h"

UBaseAbility::UBaseAbility()
{
	bIsOnCD = false;
	AbilityCharges = 0;
	AbilityCooldown = 0.f;
	AbilityCooldownCounter = 0.f;
	bHasCharges = false;
}

void UBaseAbility::UseAbility(ACharacter* character)
{
}

void UBaseAbility::CooldownLogic(float time)
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

void UBaseAbility::abilitySpecialEffect()
{
}



void UBaseAbility::setAbilityCooldown(float abilityCooldown)
{
	abilityCooldown = abilityCooldown;
}

float UBaseAbility::getAbilityCooldown()
{
	return abilityCooldown;
}

void UBaseAbility::setAbilityFlag(bool flag)
{
	flag = flag;
}