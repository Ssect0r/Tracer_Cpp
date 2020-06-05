// Fill out your copyright notice in the Description page of Project Settings.


#include "SummonerAI.h"
#include "AIAbilityManager.h"
#include "HealthComponent.h"

ASummonerAI::ASummonerAI()
{
	AbilityManager = CreateDefaultSubobject<UAIAbilityManager>(TEXT("AbilityManager"));
	
}

void ASummonerAI::BeginPlay()
{
	Super::BeginPlay();
	PrimaryActorTick.bCanEverTick = true;
	AbilityManager->setCharacter(this);
	//AbilityManager = NewObject<UAIAbilityManager>(this, UAIAbilityManager::StaticClass());
	//AbilityManager->setCharacter(this);
}


void ASummonerAI::Tick(float DeltaTime)
{
	float hp = HealthComp->getHP();
	if (HealthComp->getHP() < 50.f)
	{
		AbilityManager->SpawnMage();
	}
}

void ASummonerAI::OnPawnSeen(APawn* SeenPawn)
{
 	Super::OnPawnSeen(SeenPawn);
	if (this->GetDistanceTo(SeenPawn) <1000)
	{	
		AbilityManager->SpawnGuard();	
	}
}

void ASummonerAI::OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	Super::OnNoiseHeard(NoiseInstigator,Location,Volume);
	AbilityManager->SpawnTracker();
}

