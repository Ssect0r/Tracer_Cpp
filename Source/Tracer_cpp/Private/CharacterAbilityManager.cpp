// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAbilityManager.h"
#include "FirstAbility.h"
#include "SecondAbility.h"
#include "GameFramework/PlayerController.h"
#include "UltimateAbility.h"


void UCharacterAbilityManager::setCharacter(ACharacter* Character)
{
	character = Character;
}

float UCharacterAbilityManager::GetFirstAbilityCooldown()
{
	float Cooldown = FirstAbility->AbilityCooldown;
	return Cooldown;
}

void UCharacterAbilityManager::SetFirstAbilityCooldown(float NewCooldown)
{
	FirstAbility->AbilityCooldown = NewCooldown;
}

void UCharacterAbilityManager::SetSecondAbilityCooldown(float NewCooldown)
{
	SecondAbility->AbilityCooldown = NewCooldown;
}

float UCharacterAbilityManager::GetSecondAbilityCooldownCounter()
{
	float CooldownCounter = SecondAbility->AbilityCooldown - SecondAbility->AbilityCooldownCounter;
	return CooldownCounter;
}

// Sets default values for this component's properties
UCharacterAbilityManager::UCharacterAbilityManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	FirstAbility->setAbilityFlag(true);
	//SecondAbility->setAbilityFlag(true);
	// ...
}


// Called when the game starts
void UCharacterAbilityManager::BeginPlay()
{
	Super::BeginPlay();
	FirstAbility = NewObject<UFirstAbility>(this, UFirstAbility::StaticClass());
	//count = 0.f;
	firstAbilityCharges = FirstAbility->abilityCharges;
	FirstAbilityCooldown = FirstAbility->AbilityCooldown;
	SecondAbility = NewObject<USecondAbility>(this, USecondAbility::StaticClass());
	secondAbilityCooldownCounter = SecondAbility->AbilityCooldown;
	secondAbilityCooldown = SecondAbility->AbilityCooldown;
	SecondAbility->abilitySpecialFlag = true;
	UltimateAbility = NewObject<UUltimateAbility>(this, UUltimateAbility::StaticClass());
	ultimateAbilityCooldownCounter = 0;
	ultimateAbilityCooldown = UltimateAbility->abilityCooldown;
	character = Cast<ACharacter>(this->GetOwner());
	SecondAbility->ParentAbilityManager = this;
}


// Called every frame
void UCharacterAbilityManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//count += DeltaTime;
	FirstAbility->CooldownLogic(DeltaTime);
	//FirstAbilityCooldownLogic(DeltaTime, true, FirstAbility->abilityCharges);
	//SecondAbilityCooldownLogic(DeltaTime, SecondAbility->abilityFlag);
	SecondAbility->CooldownLogic(DeltaTime);
	UltimateAbility->CooldownLogic(DeltaTime);
	//UltimateAbilityCooldownLogic(DeltaTime, UltimateAbility->abilityFlag);
}

void UCharacterAbilityManager::lvlupFirstAbility(float decrease)
{
	FirstAbility->AbilityCooldown -= decrease;
	//GetFirstAbility()->AbilityCooldown -= decrease;
}

void UCharacterAbilityManager::lvlupSecondAbility(float decrease)
{
	SecondAbility->AbilityCooldown -= decrease;
	//GetSecondAbility()->abilityCooldown -= decrease;
}

void UCharacterAbilityManager::lvlupUltimateAbility()
{
}

int UCharacterAbilityManager::GetFirstAbilityCharges()
{
	return FirstAbility->AbilityChargesActual;
}

void UCharacterAbilityManager::SetFirstAbilityCooldownCounter(float value)
{
	FirstAbility->AbilityCooldownCounter = value;
}

void UCharacterAbilityManager::SetUltimateSpecialFlagReady()
{
	UltimateAbility->abilitySpecialFlag = true;
}

bool UCharacterAbilityManager::bIsAbleToRestartDamageCounter()
{
	UUltimateAbility* Ulti = Cast<UUltimateAbility>(UltimateAbility);
	if (Ulti)
	{
		bool bRestart;
		if (Ulti->bRestartDamageCounter)
		{
			bRestart = true;
		}
		else
		{
			bRestart = false;
		}
		Ulti->bRestartDamageCounter = false;
		return bRestart;
	}
	return false;
}

float UCharacterAbilityManager::GetFirstAbilityCooldownCounter()
{
	return FirstAbility->AbilityCooldownCounter;
}

float UCharacterAbilityManager::GetFirstAbilityChargesCooldown()
{
	float ActualCooldown = FirstAbility->AbilityCooldown - GetFirstAbilityCooldownCounter();
	return ActualCooldown;
}

float UCharacterAbilityManager::GetSecondAbilityCooldown()
{
	float Cooldown = SecondAbility->AbilityCooldown;
	return Cooldown;
}

float UCharacterAbilityManager::GetUltimateAbilityCooldown()
{
	float ActualCooldown = UltimateAbility->AbilityCooldown - UltimateAbility->AbilityCooldownCounter;
	return ActualCooldown;
}

bool UCharacterAbilityManager::GetSecondAbilityHealFlag()
{
	bool temp = false;
	USecondAbility* ability = Cast<USecondAbility>(SecondAbility);
	if (ability)
	{
		temp = ability->GetHealFlag();
	}
	return temp;
}

void UCharacterAbilityManager::SetSecondAbilityHealFlag(bool flag)
{
	USecondAbility* ability = Cast<USecondAbility>(SecondAbility);
	if (ability)
	{
		ability->SetHealFlag(flag);
	}
}

void UCharacterAbilityManager::UseAbility(EAbilityType AbilityType)
{
	switch (AbilityType)
	{
	case EAbilityType::PRIMARY:
		FirstAbility->UseAbility(character);
		break;
	case EAbilityType::SECONDARY:
		SecondAbility->UseAbility(character);
			//if (SecondAbility->abilityFlag == false && SecondAbility->abilitySpecialFlag == true)
			//{
			//	secondAbilityCooldownCounter = 0.f;
			//	count = 0.f;
			//}
			//SecondAbility->abilitySpecialFlag = false;
		break;
	case EAbilityType::ULTIMATE:
		UltimateAbility->UseAbility(character);
		break;
	}
}

//void UCharacterAbilityManager::FirstAbilityCooldownLogic(float time, bool firstAbilityFlag, int charges)
//{
//	if (FirstAbility->abilityCharges < firstAbilityCharges)
//	{
//		if (firstAbilityCooldownCounter <= FirstAbility->abilityCooldown)
//		{
//			firstAbilityCooldownCounter += time;
//		}
//		else
//		{
//			firstAbilityCooldownCounter = 0.f;
//			FirstAbility->abilityCharges++;
//		}
//	}
//}


//void UCharacterAbilityManager::SecondAbilityCooldownLogic(float time, bool abilityFlag, int charges)
//{
//	if (count < SecondAbility->abilityTime && SecondAbility->abilityFlag)
//	{
//		SecondAbility->characterPositionArray.Add(character->GetActorTransform());
//	}
//	else if (SecondAbility->characterPositionArray.Num() > 0 && SecondAbility->abilityFlag)
//	{
//		SecondAbility->characterPositionArray.RemoveAt(0);
//		SecondAbility->characterPositionArray.Add(character->GetActorTransform());
//	}
//	if (count >= SecondAbility->abilityTime)
//	{
//		APlayerController* PC = Cast<APlayerController>(character->Controller);
//		if (PC)
//		{
//			character->EnableInput(PC);
//		}
//	}
//	if (!SecondAbility->abilityFlag)
//	{
//		if (secondAbilityCooldownCounter <= SecondAbility->abilityCooldown)
//		{
//			secondAbilityCooldownCounter += time;
//			if (SecondAbility->characterPositionArray.Num() > 0 && count <= SecondAbility->abilityTime)
//			{
//				GetOwner()->bCanBeDamaged = false;
//				FRotator actorRotation = SecondAbility->characterPositionArray.Last().GetRotation().Rotator();
//				FVector actorLocation = SecondAbility->characterPositionArray.Last().GetLocation();
//				int previousLocation = SecondAbility->characterPositionArray.Num() - 1;
//
//				character->SetActorLocation(actorLocation);
//				character->GetController()->SetControlRotation(actorRotation);
//				SecondAbility->characterPositionArray.RemoveAt(previousLocation);
//			}
//			else
//			{
//				GetOwner()->bCanBeDamaged = true;	
//			}
//		}
//		else
//		{
//			SecondAbility->abilityFlag = true;		
//		}
//	}
//	else
//	{
//		//SecondAbility->abilitySpecialFlag = true;
//		SetSecondAbilityHealFlag(true);
//		secondAbilityCooldownCounter = 0.f;
//		count = 0.f;
//	}
//}



//void UCharacterAbilityManager::UltimateAbilityCooldownLogic(float time, bool abilityFlag, int charges)
//{
//	if (!UltimateAbility->abilityFlag)
//	{
//		if (ultimateAbilityCooldownCounter <= UltimateAbility->abilityCooldown)
//		{
//			ultimateAbilityCooldownCounter += time;
//		}
//		else
//		{
//			UltimateAbility->abilityFlag = true;
//			ultimateAbilityCooldownCounter = 0.f;
//		}
//	}
//}


