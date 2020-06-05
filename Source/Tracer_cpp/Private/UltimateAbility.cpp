// Fill out your copyright notice in the Description page of Project Settings.


#include "UltimateAbility.h"
#include "Tracer_cppCharacter.h"
#include "Tracer_Ultimate.h"
#include "Components/StaticMeshComponent.h"

UUltimateAbility::UUltimateAbility()
{
	//abilityCooldown = 12.f;
	AbilityCooldown = 12.0f;
	//abilityCharges = 3;
	bHasCharges = false;
	bIsOnCD = false;
	abilitySpecialFlag = false;
}

void UUltimateAbility::UseAbility(ACharacter* character)
{
	//UE_LOG(LogTemp, Warning, TEXT("Ultimate Ability"));
	
		if (!bIsOnCD && abilitySpecialFlag)
		{
			if (character)

			{
			
				const FRotator SpawnRotation = character->GetActorRotation().GetEquivalentRotator();
				const FVector SpawnLocation = character->GetActorLocation();

				FActorSpawnParameters ActorSpawnParams;
				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
				ATracer_cppCharacter* tracerCharacter = Cast<ATracer_cppCharacter>(character);
				if (tracerCharacter)
				{
					ATracer_Ultimate* bombRef = GetWorld()->SpawnActor<ATracer_Ultimate>(tracerCharacter->UltimateProjectileClass, SpawnLocation + character->GetActorForwardVector() + FVector(0, 0, 75), SpawnRotation, ActorSpawnParams);
				}
			}
		
		//abilityFlag = false;
		bIsOnCD = true;
		abilitySpecialFlag = false;
		bRestartDamageCounter = true;
	}
	else
	{
		bRestartDamageCounter = false;
		UE_LOG(LogTemp, Warning, TEXT("Ultimate on cooldown"));
	}
}