 // Fill out your copyright notice in the Description page of Project Settings.


#include "FirstAbility.h"
#include "Tracer_cppCharacter.h"
#include "DrawDebugHelpers.h"

UFirstAbility::UFirstAbility()
{
	//abilityFlag = true;
	//abilityCooldown = 6.0f;
	AbilityCooldown = 6.0f;
	//abilityCharges = 3;
	AbilityCharges = 3;
	AbilityChargesActual = 3;
	bHasCharges = true;
}


void UFirstAbility::UseAbility(ACharacter* character)
{
	if (AbilityCharges != 3)
	{
		bIsOnCD = true;
	}
	else
	{
		bIsOnCD = false;
	}
	if (character)
	{
			FHitResult hit;
			FVector forwardVector = character->GetActorForwardVector();
			FVector playerLocation = character->GetActorLocation();
			FVector blinkDestinationLocation = playerLocation + forwardVector * 600;
			FCollisionQueryParams collisionParams;
			bool isHit = GetWorld()->LineTraceSingleByChannel(hit, playerLocation, blinkDestinationLocation, ECC_Visibility);
			//if (Cast<ATracer_cppCharacter>(character))
			//{
				if (AbilityChargesActual > 0)
				{
					if (isHit)
					{

						if (hit.bBlockingHit)
						{
							blinkDestinationLocation = hit.Location;
							character->SetActorLocation(blinkDestinationLocation);
							//abilityFlag = false;
							bIsOnCD = true;
							AbilityChargesActual--;
						}
					}
					else
					{
						character->SetActorLocation(blinkDestinationLocation);
						//abilityFlag = false;
						bIsOnCD = true;
						AbilityChargesActual--;
					}
				}
				UE_LOG(LogTemp, Warning, TEXT("First Ability"));
				bIsOnCD = true;
			}
	}





