// Fill out your copyright notice in the Description page of Project Settings.


#include "AIGuard.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TimerManager.h"
#include "Runtime/Core/Public/Delegates/DelegateSignatureImpl.inl"
#include <Runtime\AIModule\Classes\Blueprint\AIBlueprintHelperLibrary.h>
#include "HealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/GameFramework/PawnMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Tracer_cppProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "math.h"
#include "Tracer_cppCharacter.h"
#include "Tracer_Ultimate.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
AAIGuard::AAIGuard()
{
	PrimaryActorTick.bCanEverTick = true;
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSensingComponent->OnSeePawn.AddDynamic(this, &AAIGuard::OnPawnSeen);
	PawnSensingComponent->OnHearNoise.AddDynamic(this, &AAIGuard::OnNoiseHeard);
	OriginalOrientation = GetControlRotation();
	bDied = false;
	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(false);			// only the owning player will see this mesh
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	FP_Gun->SetupAttachment(GetMesh(), TEXT("Gun"));

	FP_MuzzleLocationL = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocationL->SetupAttachment(FP_Gun);
	RangeOfFollow = 1500.f;
	RangeOfShooting = 700.f;
	bIsSummoned = false;
	OverlapCheckArea = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxObject"));
	OverlapCheckArea->SetGenerateOverlapEvents(true);
	OverlapCheckArea->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AAIGuard::BeginPlay()
{
	Super::BeginPlay();
	// Zakomentowalem wszystkie uzycia patrolu, bo stwierdzilem, ze i tak go nie bede uzywac
	OriginalLocation = GetActorLocation();

	if (shouldPatrol)
	{
		//Patrol();
	}
	HealthComp->OnHealthChanged.AddDynamic(this, &AAIGuard::OnHealthChanged);
	OverlapCheckArea->OnComponentBeginOverlap.AddDynamic(this, &AAIGuard::BeginOverlap);
	OverlapCheckArea->OnComponentEndOverlap.AddDynamic(this, &AAIGuard::OnOverlapEnd);
	UGameplayStatics::PlaySoundAtLocation(this, SpawnSound, GetActorLocation());
}

void AAIGuard::OnPawnSeen(APawn* SeenPawn)
{
	if (!bDied)
	{
		if (SeenPawn == nullptr)
		{
			return;
			bShooting = false;
		}
		if (bShouldRetreat)
		{
			RetreatEnemySeen();
		}
		else {
			FVector Direction = SeenPawn->GetActorLocation() - GetActorLocation();
			Direction.Normalize();
			FRotator NewLookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
			NewLookAt.Pitch = 0.0f;
			NewLookAt.Roll = 0.0f;
			SetActorRotation(NewLookAt);

			if (this->GetDistanceTo(SeenPawn) < RangeOfFollow && !bSpread) {
				shouldPatrol = false;
				UAIBlueprintHelperLibrary::SimpleMoveToActor(GetController(), SeenPawn);
				if (this->GetDistanceTo(SeenPawn) <= RangeOfShooting)
				{
					bTargetInSight = true;
					if (!bAbleToStop)
					{
						GetMovementComponent()->StopMovementImmediately();
					}
					bShooting = true;
					Shoot(FP_MuzzleLocationL);
				}
				else
				{
					bShooting = false;
					bTargetInSight = false;
				}
			}
			else if (CurrentPatrolPoint && bIsAbleToPatrol)
			{
				shouldPatrol = true;
			//	Patrol();
				bShooting = false;
				bTargetInSight = false;
			}
			else
			{
				bTargetInSight = false;
				shouldPatrol = false;
				bShooting = false;
				if(!bAbleToStop)
				GetMovementComponent()->StopMovementImmediately();
			}
			bTargetInSight = false;
		}
	}
}

void AAIGuard::RetreatEnemySeen()
{
	FCollisionQueryParams collisionParams(FCollisionQueryParams::DefaultQueryParam);
	FHitResult hit;
	bool isHit = GetWorld()->LineTraceSingleByChannel(hit, this->GetActorLocation(), this->GetActorLocation() + this->GetActorForwardVector() * -1000, ECC_MAX, collisionParams);

	if (isHit)
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), this->GetActorLocation() + this->GetActorForwardVector() * -1500);
	}
}

void AAIGuard::Patrol()
{
	if (!bDied)
	{
		if (FirstPatrolPoint == nullptr || CurrentPatrolPoint == SecondPatrolPoint)
		{
			CurrentPatrolPoint = FirstPatrolPoint;
		}
		else
		{
			CurrentPatrolPoint = SecondPatrolPoint;
		}
		UAIBlueprintHelperLibrary::SimpleMoveToActor(GetController(), CurrentPatrolPoint);
	}
}

void AAIGuard::OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	if (!bDied && !bTargetInSight)
	{
		if (Instigator == nullptr)
		{
			return;
		}
		//DrawDebugSphere(GetWorld(), Location, 32.0f, 12, FColor::Purple, false, 10.f);
		if (HealthComp->getHP() > HPToRetreat && !bSpread)
		{
			FVector Direction = Location - GetActorLocation();
			Direction.Normalize();

			FRotator NewLookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
			NewLookAt.Pitch = 0.0f;
			NewLookAt.Roll = 0.0f;
			SetActorRotation(NewLookAt);

			GetWorldTimerManager().ClearTimer(TimerHandle_ResetOrientation);
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), Location);

			//GetWorld()->GetTimerManager().SetTimer(TimerHandle_ResetOrientation, this, &AAIGuard::ResetOrientation, 1.0f);   // Bug in ai behavior
			CurrentPatrolPoint = FirstPatrolPoint;
			shouldPatrol = true;
			//Patrol();
		}
		else if( HealthComp->getHP() <= HPToRetreat && bIsAbleToRetreat)
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), Location + this->GetActorForwardVector() * 1500);
		}
	}
}

void AAIGuard::OnHealthChanged(UHealthComponent* HealthComponent, float Health1, float HealthDelta, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	ATracer_cppCharacter* player = Cast<ATracer_cppCharacter>(DamageCauser);
	if (player)
	{
		player->DamageProgressToFinishLevel += HealthDelta ;
	}

	if(Health1 <= HPToRetreat && bIsAbleToRetreat)
		{
		bShouldRetreat = true;
		}

	if (Health1 <= 0.0f && !HealthComponent->isDead() && !bDied)
	{
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
		GetMovementComponent()->StopMovementImmediately();
		HealthComponent->bDied=true;
		bDied = true;
		SetLifeSpan(5.f);
		
		if (!bIsSummoned && HealthComp->isKilledByPlayer)
		{
			ATracer_cppCharacter* player = Cast<ATracer_cppCharacter>(DamageCauser);
			
			if (player)
			{
				player->KillCountIncrease();
			}
			else
			{
				ATracer_Ultimate* ultimate = Cast<ATracer_Ultimate>(DamageCauser);
				if(ultimate)
				{
					ATracer_cppCharacter* thePlayer = Cast<ATracer_cppCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
					if (thePlayer)
					{
						thePlayer->KillCountIncrease();
					}
				}
			}
		}
	}
}

void AAIGuard::ResetOrientation()
{
	SetActorRotation(OriginalOrientation);
}

void AAIGuard::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	ATracer_Ultimate* ultimate = Cast<ATracer_Ultimate>(OtherActor);
	if (ultimate)
	{
		bSpread = true;
		FCollisionQueryParams collisionParams(FCollisionQueryParams::DefaultQueryParam);
		FHitResult hit;
		bool isHit = GetWorld()->LineTraceSingleByChannel(hit, this->GetActorLocation(), ultimate->GetActorLocation() + this->GetActorForwardVector() * -500, ECC_Pawn, collisionParams);
		if (isHit)
		{
			isHit = GetWorld()->LineTraceSingleByChannel(hit, this->GetActorLocation(), ultimate->GetActorLocation() + (-1 *this->GetActorForwardVector()) * -500, ECC_Pawn, collisionParams);
			if (isHit)
			{
				isHit = GetWorld()->LineTraceSingleByChannel(hit, this->GetActorLocation(), ultimate->GetActorLocation() + this->GetActorRightVector() * -500, ECC_Pawn, collisionParams);
				if (isHit)
				{
					isHit = GetWorld()->LineTraceSingleByChannel(hit, this->GetActorLocation(), ultimate->GetActorLocation() + (-1 * this->GetActorRightVector()) * -500, ECC_Pawn, collisionParams);
					if (!isHit)
					{
						UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), ultimate->GetActorLocation() + (-1 * this->GetActorRightVector()) * -500);
					}
					else
					{
						bSpread = false;
					}

				}
				else
				{
					UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), ultimate->GetActorLocation() + this->GetActorRightVector() * -500);
				}
			}
			else
			{
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), ultimate->GetActorLocation() + (-1 * this->GetActorForwardVector()) * -500);
			}
		}
		else
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), ultimate->GetActorLocation() + this->GetActorForwardVector() * -500);
		}

		UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), ultimate->GetActorLocation() + this->GetActorForwardVector() * -500);
	}
}

void AAIGuard::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ATracer_Ultimate* ultimate = Cast<ATracer_Ultimate>(OtherActor);
	if (ultimate && OverlappedComp == OverlapCheckArea)
	{
		bSpread = false;
	}
}

// Called every frame
void AAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//if (!bDied)
	//{
	//	//if (bIsAbleToPatrol && CurrentPatrolPoint )
	//	//{
	//	//	FVector Distance = GetActorLocation() - CurrentPatrolPoint->GetActorLocation();
	//	//	float DistanceAsFloat = Distance.Size();

	//	//	if (DistanceAsFloat < 100)
	//	//	{
	//	//		if (shouldPatrol)
	//	//		{
	//	//			//Patrol();
	//	//		}
	//	//	}
	//	//}
	//	//// Nieudana proba zmuszenia botow do unikania wybuchu bomby
	//	//	TArray<AActor*> OverlappedActors;
	//	//OverlapCheckArea->GetOverlappingActors(OverlappedActors);
	//	//for (AActor* Overlap : OverlappedActors)
	//	//{
	//	//	ATracer_Ultimate* Ultimate = Cast<ATracer_Ultimate>(Overlap);
	//	//	if (Ultimate)
	//	//	{
	//	//		Ultimate->GetActorLocation();
	//	//		UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), Ultimate->GetActorLocation() + GetActorForwardVector() * -1 * 400);
	//	//	}
	//	//}
	//	//if (bSpread && SpreadTime <=8.f)
	//	//{
	//	//	SpreadTime += DeltaTime;
	//	//}
	//	//else
	//	//{
	//	//	bSpread = false;
	//	//	SpreadTime = 0.f;
	//	//}
	//}
	if (bSpread)
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), this->GetActorLocation() + this->GetActorForwardVector() * -500);
	}
}

void AAIGuard::SetbIsSummoned(bool bSummoned)
{
	bIsSummoned = bSummoned;
}

void AAIGuard::Shoot(USceneComponent* muzzle)
{
	UWorld* const World = GetWorld();
	if (World != NULL)
	{
		const FRotator SpawnRotation = GetControlRotation();
		const FVector SpawnLocation = FP_MuzzleLocationL->GetComponentLocation();
		FActorSpawnParameters ActorSpawnParams;
		FCollisionQueryParams collisionParams(FCollisionQueryParams::DefaultQueryParam);
		TSubclassOf<UDamageType> P;
		FHitResult hit;

		FVector ForwardVector = GetRootComponent()->GetForwardVector();

		float HalfRad = FMath::DegreesToRadians(BulletSpread);
		ForwardVector = FMath::VRandCone(ForwardVector, HalfRad, HalfRad);
		FVector bulletDestinationLocation = ((ForwardVector * RangeOfBullets) + SpawnLocation);

		//ActorSpawnParams.Instigator = this;
		bool isHit = GetWorld()->LineTraceSingleByChannel(hit, SpawnLocation, bulletDestinationLocation, ECC_Pawn, collisionParams);
		if (isHit)
		{
			if (hit.bBlockingHit)
			{
				bulletDestinationLocation = hit.Location;
				World->SpawnActor<ATracer_cppProjectile>(ProjectileClass, hit.Location, SpawnRotation, ActorSpawnParams);
				UGameplayStatics::PlaySoundAtLocation(this, ShootSound, GetActorLocation());
				if (hit.GetActor() != nullptr) {
					if (hit.Actor.Get()->bCanBeDamaged)
					{
						UGameplayStatics::ApplyPointDamage(hit.GetActor(), BulletDamage, this->GetActorLocation(), hit, nullptr, this, P);
					}
					if (TraceEffect)
					{
						FVector Location = FP_MuzzleLocationL->GetComponentLocation();
						UParticleSystemComponent* TraceComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TraceEffect, SpawnLocation);
						if (TraceComp)
						{
							TraceComp->SetVectorParameter("BeamEnd", bulletDestinationLocation);
						}
					}
				}
			}
		}
	}
}
