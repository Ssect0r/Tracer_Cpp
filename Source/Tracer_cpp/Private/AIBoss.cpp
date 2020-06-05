// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBoss.h"
#include "AIAbilityManager.h"
#include "HealthComponent.h"

AAIBoss::AAIBoss()
{
	AbilityManager = CreateDefaultSubobject<UAIAbilityManager>(TEXT("AbilityManager"));
}

void AAIBoss::Tick(float DeltaTime)
{
	float hp = HealthComp->getHP();
	if (HealthComp->getHP() < 2500.f)
	{
		AbilityManager->BossSpawnSummoner();
	}
}

void AAIBoss::OnPawnSeen(APawn* SeenPawn)
{
	Super::OnPawnSeen(SeenPawn);
	AbilityManager->SpawnGuard();
	AbilityManager->SpawnMage();
	AbilityManager->SpawnTracker();
	AbilityManager->BossSpawnFireBall();
	AbilityManager->BossSpawnBouncingFireBall();
}

void AAIBoss::OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	Super::OnNoiseHeard(NoiseInstigator, Location, Volume);
	AbilityManager->SpawnTracker();
}

void AAIBoss::BeginPlay()
{
	Super::BeginPlay();
	AbilityManager->setCharacter(this);
	AbilityManager->SpawnRotatingOrb();
}
