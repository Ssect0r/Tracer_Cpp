// Fill out your copyright notice in the Description page of Project Settings.


#include "AIAbilityManager.h"
#include "AISummonAbility.h"
#include "AIBlink.h"
#include "AIGuard.h"
#include "AIRotatingOrbAbility.h"
#include "Components/StaticMeshComponent.h"
#include "RotatingOrb.h"

UAIAbilityManager::UAIAbilityManager()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UAIAbilityManager::BeginPlay()
{
	//SummonAbility = NewObject<UAISummonAbility>(this, UAISummonAbility::StaticClass());
	int i = 0;

	for (TSubclassOf<UAIBaseAbility> BaseAbility : AbilityArray)
	{
		FString AbilityName = "Ability" + i;
		if (BaseAbility)
		{
			UAIBaseAbility* curAbility = Cast<UAIBaseAbility>(BaseAbility->GetDefaultObject());
			if (curAbility)
			{
				curAbility->ParentAbilityManager = this;
				GameplayAbilityArray.Add(curAbility);
			}
			i++;
		}
	}
	
}

UAIBaseAbility* UAIAbilityManager::FindAbilityFunction(int Index)
{
	UAIBaseAbility* FoundAbility = nullptr;
	FoundAbility = GameplayAbilityArray[Index];
	if (Index == 0 || Index == 1 || Index == 2 || Index == 3 || Index == 4 || Index == 5 || Index == 6)
	{
		UAIBaseAbility* CastedFoundAbility = Cast<UAIBaseAbility>(FoundAbility);
		if(CastedFoundAbility)
		{
			FoundAbility = CastedFoundAbility;
		}
	}
	return FoundAbility;
}

void UAIAbilityManager::SpawnTracker()
{
	UAIBaseAbility* Ability = FindAbilityFunction(0);
	if (Ability)
	{
		Ability->UseAbility(character);
	}
}

void UAIAbilityManager::SpawnGuard()
{
	UAIBaseAbility* Ability = FindAbilityFunction(1);
	if (Ability)
	{
		Ability->UseAbility(character);
	}
}

void UAIAbilityManager::SpawnMage()
{
	UAIBaseAbility* Ability = FindAbilityFunction(2);
	if (Ability)
	{
		Ability->UseAbility(character);
	}
}

void UAIAbilityManager::SpawnRotatingOrb()
{
	UAIBaseAbility* Ability = FindAbilityFunction(5);
	if (Ability)
	{
		
		Ability->UseAbility(character);
	}
}

void UAIAbilityManager::SpawnFireBall()
{
	UAIBaseAbility* Ability = FindAbilityFunction(0);
	if (Ability)
	{
		Ability->UseAbility(character);
	}
}

void UAIAbilityManager::SpawnBouncingFireBall()
{
	UAIBaseAbility* Ability = FindAbilityFunction(2);
	if (Ability)
	{
		Ability->UseAbility(character);
	}
}

void UAIAbilityManager::BlinkToTarget()
{
	UAIBaseAbility* Ability = FindAbilityFunction(1);
	if (Ability)
	{
		Ability->UseAbility(character);
	}
}

void UAIAbilityManager::BossSpawnFireBall()
{
	UAIBaseAbility* Ability = FindAbilityFunction(3);
	if (Ability)
	{
		Ability->UseAbility(character);
	}
}

void UAIAbilityManager::BossSpawnBouncingFireBall()
{
	UAIBaseAbility* Ability = FindAbilityFunction(4);
	if (Ability)
	{
		Ability->UseAbility(character);
	}
}

void UAIAbilityManager::BossSpawnSummoner()
{
	UAIBaseAbility* Ability = FindAbilityFunction(6);
	if (Ability)
	{
		Ability->UseAbility(character);
	}
}



APawn* UAIAbilityManager::SpawnEnemy(TSubclassOf<APawn> ClassToSpawn)
{
	FVector PawnLocation = GetOwner()->GetActorLocation() + FVector(0,50,0);
	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	APawn* curSpawn = GetWorld()->SpawnActor<APawn>(ClassToSpawn, PawnLocation + GetOwner()->GetActorForwardVector() *100, FRotator(0.0f), params);
	if (curSpawn)
	{
		curSpawn->SetOwner(character);
		AAIGuard* bot = Cast<AAIGuard>(curSpawn);
			if(bot)
			{
				bot->SetbIsSummoned(true);
			}
	}
	return curSpawn;
}

//
//// Sets default values for this component's properties
//UAIAbilityManager::UAIAbilityManager()
//{
//	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
//	// off to improve performance if you don't need them.
//	PrimaryComponentTick.bCanEverTick = true;
//	
//	//SecondAbility = NewObject<UFirstAbility>(this, UFirstAbility::StaticClass());
//	FirstAbilityFlag = true;
//
//	// ...
//}
//
//
//// Called when the game starts
//void UAIAbilityManager::BeginPlay()
//{
//	Super::BeginPlay();
//	FirstAbility = NewObject<UFirstAbility>(this, UFirstAbility::StaticClass());
//	character = Cast<ACharacter>(this->GetOwner());
//	// ...
//	
//}
//
//
//// Called every frame
void UAIAbilityManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	for (UAIBaseAbility* ability : GameplayAbilityArray)
	{
		ability->CooldownLogic(DeltaTime);
	}
}
AActor* UAIAbilityManager::SpawnOrb(TSubclassOf<AActor> ClassToSpawn)
{
	FVector PawnLocation = GetOwner()->GetActorLocation() + FVector(0, 50, 0);
	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	AActor* curSpawn = GetWorld()->SpawnActor<AActor>(ClassToSpawn, PawnLocation + GetOwner()->GetActorForwardVector() * 100, FRotator(0.0f), params);
	if (curSpawn)
	{
		ARotatingOrb* RotatingOrb = Cast<ARotatingOrb>(curSpawn);
		{
			RotatingOrb->SetHost(this->GetOwner());
		}
	}
	return curSpawn;
}

//
void UAIAbilityManager::setCharacter(ACharacter* Character)
{
	character = Character;
}
void UAIAbilityManager::SetTarget(APawn* Target)
{
	UAIBaseAbility* Ability = FindAbilityFunction(1);
		UAIBlink* Blink = Cast<UAIBlink>(Ability);
		if (Blink)
		{
			Blink->SetTarget(Target);
		}
}
//
//void UAIAbilityManager::BlinkAbilityCooldownLogic(float time, bool abilityFlag)
//{
//	if (firstAbilityCooldownCounter <= FirstAbility->abilityCooldown)
//	{
//		firstAbilityCooldownCounter += time;
//	}
//	else
//	{
//		firstAbilityCooldownCounter = 0.f;
//		FirstAbility->abilityFlag = true;
//	}
//}
//
//void UAIAbilityManager::UseBlink(ACharacter* character, FVector target)
//{
//	if (FirstAbility->abilityFlag)
//	{
//		FirstAbility->AIUseAbility(character, target);
//	}
//}
//
//void UAIAbilityManager::Summon(ACharacter* character)
//{
//	FActorSpawnParameters params;
//	ATrackerBot* curBot = GetWorld()->SpawnActor<ATrackerBot>(SummonClass, character->GetPawnViewLocation() + FVector(100,100,100), FRotator(0.0f), params);
//	curBot->AutoPossessAI;
//}
//
//void UAIAbilityManager::SecondAbilityCooldownLogic(float time, int charges)
//{
	//if(SecondAbilityCooldownCounter <= SecondAbility->abilityCooldown)
	//{ }
//}


