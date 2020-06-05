// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{

	Health = 100.f;
	MaxHealth = 100.f;
	TimeOfDeath = 2.f;
	bDied = false;
	TeamNumber = 0;
	isKilledByPlayer;
	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* MyOwner = GetOwner();
	if (MyOwner)
	{
		MyOwner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::HandleTakeAnyDamage);
	}
	
}

void UHealthComponent::HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f)
	{
		return;
	}

	if (DamageCauser != DamagedActor && isFriendly(DamagedActor, DamageCauser))
	{
		return;
	}
	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);

	if (Health <= 0)
	{
		class ATracer_cppCharacter* player = Cast<ATracer_cppCharacter>(DamageCauser);
		class ATracer_Ultimate* ultimate = Cast<ATracer_Ultimate>(DamageCauser);
			if(player || ultimate)
			{
				isKilledByPlayer = true;
			}
	}
	//UE_LOG(LogTemp, Log, TEXT("Health Changed: %s"), *FString::SanitizeFloat(Health));

	OnHealthChanged.Broadcast(this, Health, Damage, DamageType, InstigatedBy, DamageCauser);
}

bool UHealthComponent::isDead()
{
	return bDied;
}

void UHealthComponent::setDead()
{
	bDied = true;
}

float UHealthComponent::getHP()
{
	return Health;
}

void UHealthComponent::Heal()
{
	Health = MaxHealth;
}

bool UHealthComponent::isFriendly(AActor* ActorA, AActor* ActorB)
{
	if (ActorA == nullptr && ActorB == nullptr)
	{
		return true;
	}
	if (ActorA == nullptr || ActorB == nullptr)
	{
		return true;
	}

	UHealthComponent* HealthCompA = Cast<UHealthComponent>(ActorA->GetComponentByClass(UHealthComponent::StaticClass()));
	UHealthComponent* HealthCompB = Cast<UHealthComponent>(ActorB->GetComponentByClass(UHealthComponent::StaticClass()));

	if (HealthCompA == nullptr || HealthCompB == nullptr)
	{
		return true;
	}

	return HealthCompA->TeamNumber == HealthCompB->TeamNumber;
}


