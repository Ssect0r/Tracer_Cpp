// Fill out your copyright notice in the Description page of Project Settings.


#include "MageAI.h"
#include "AIAbilityManager.h"
#include "AIBlink.h"

AMageAI::AMageAI()
{
	AbilityManager = CreateDefaultSubobject<UAIAbilityManager>(TEXT("AbilityManager"));
	RangeToBlink = 1500.f;
	RangeToFireball = 700.f;
	//AbilityManager->setCharacter(this);
}

void AMageAI::BeginPlay()
{
	Super::BeginPlay();
	AbilityManager->setCharacter(this);
}

void AMageAI::Tick(float DeltaTime)
{
}

void AMageAI::OnPawnSeen(APawn* SeenPawn)
{
	Super::OnPawnSeen(SeenPawn);
	AbilityManager->SetTarget(SeenPawn);
	if (this->GetDistanceTo(SeenPawn) > RangeToBlink)
	{
		
		AbilityManager->BlinkToTarget();
		
	}
	if (this->GetDistanceTo(SeenPawn) < RangeToFireball)
	{
		AbilityManager->SpawnFireBall();
	}

	if (this->GetDistanceTo(SeenPawn) > RangeToFireball)
	{
		AbilityManager->SpawnBouncingFireBall();
	}
}

void AMageAI::OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	Super::OnNoiseHeard(NoiseInstigator, Location, Volume);
}


