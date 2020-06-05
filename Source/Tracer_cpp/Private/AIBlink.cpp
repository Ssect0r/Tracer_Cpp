// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBlink.h"
#include "AIGuard.h"
#include "Engine\World.h"
#include "Kismet/GameplayStatics.h"

UAIBlink::UAIBlink()
{
	AbilityCooldown = 5.f;
	AbilityCharges = 3;
	bIsOnCD = false;
	bHasCharges = true;
	AbilityName = "BlinkAbility";
	Fname = (*AbilityName);
}


void UAIBlink::SetTarget(APawn* targetActor)
{
	Target = targetActor;
}

void UAIBlink::UseAbility(ACharacter* character)
{
	FHitResult hit;
	FVector forwardVector = character->GetActorForwardVector();
	FVector playerLocation = character->GetActorLocation();
	FVector blinkDestinationLocation = (character->GetActorForwardVector() + (Target->GetActorLocation()  - character->GetActorLocation()/2));
	FCollisionQueryParams collisionParams;
	bool isHit = GetWorld()->LineTraceSingleByChannel(hit, playerLocation, blinkDestinationLocation, ECC_Visibility);
	if (isHit)
	{

		if (hit.bBlockingHit)
		{
			blinkDestinationLocation = hit.Location;
			character->SetActorLocation(blinkDestinationLocation);
			bIsOnCD = true;
		}
	}
	else
	{
 		character->SetActorLocation(blinkDestinationLocation);
		bIsOnCD = false;
	}
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BlinkEffect, blinkDestinationLocation);
}
