// Fill out your copyright notice in the Description page of Project Settings.


#include "SecondAbility.h"
#include "CharacterAbilityManager.h"
#include "GameFramework/PlayerController.h"

USecondAbility::USecondAbility()
{
	//abilityCooldown = 12.0f;
	//abilityTime = 3.f;
	//abilityFlag = true;
	//abilitySpecialFlag = true;

	bHasCharges = false;
	AbilityCooldown = 12.0f;
	bIsOnCD = false;
}


void USecondAbility::SetHealFlag(bool flag)
{
	HealFlag = flag;
}

void USecondAbility::CooldownLogic(float time)
{
	Super::CooldownLogic(time);
	AbilityTimeCounter += time;
	if (AbilityTimeCounter < AbilityTime && !bIsOnCD)
	{
		CharacterPositionArray.Add(ParentAbilityManager->character->GetActorTransform());
		
	}
	else if(CharacterPositionArray.Num() > 0 && !bIsOnCD)
	{
		CharacterPositionArray.RemoveAt(0);
		CharacterPositionArray.Add(ParentAbilityManager->character->GetActorTransform());
	}

	if (AbilityTimeCounter >= AbilityTime)
	{
		APlayerController* PC = Cast<APlayerController>(ParentAbilityManager->character->Controller);
		if (PC)
		{
			ParentAbilityManager->character->EnableInput(PC);
		}
	}

	if (bIsOnCD)
	{
		if (AbilityCooldownCounter <= AbilityCooldown)
		{
			if (CharacterPositionArray.Num() > 0 && AbilityTimeCounter <= AbilityTime)
			{
				ParentAbilityManager->GetOwner()->bCanBeDamaged = false;
				FRotator ActorRotation = CharacterPositionArray.Last().GetRotation().Rotator();
				FVector ActorLocation = CharacterPositionArray.Last().GetLocation();
				int PreviousLocation = CharacterPositionArray.Num() - 1;

				ParentAbilityManager->character->SetActorLocation(ActorLocation);
				ParentAbilityManager->character->GetController()->SetControlRotation(ActorRotation);
				CharacterPositionArray.RemoveAt(PreviousLocation);
			}
			else
			{
				ParentAbilityManager->GetOwner()->bCanBeDamaged = true;
				CharacterPositionArray.Empty();
			}
		}
		else
		{
			bIsOnCD = false;
		}
	}
	else
	{
		ParentAbilityManager->SetSecondAbilityHealFlag(true);
		AbilityCooldownCounter = 0.f;
		AbilityTimeCounter = 0.f;
	}
}

void USecondAbility::UseAbility(ACharacter* character)
{
	if (character)
	{
		if (!bIsOnCD)
		{
			UE_LOG(LogTemp, Warning, TEXT("Second Ability"));
			APlayerController* PC = Cast<APlayerController>(character->Controller);
			if (PC)
			{
				character->DisableInput(PC);
			}
			//abilityFlag = false;
			bIsOnCD = true;
			//SabilitySpecialFlag = false;
			HealFlag = false;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Second Ability is on cooldown"));
			HealFlag = false;
		}
	}
}