// Fill out your copyright notice in the Description page of Project Settings.


#include "TrackerBot.h"
#include "Components/StaticMeshComponent.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "HealthComponent.h"
#include "Materials/MaterialInstance.h"
#include "Components/SphereComponent.h"
#include "Tracer_cppCharacter.h"
#include "TimerManager.h"


// Sets default values
ATrackerBot::ATrackerBot()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	MeshComp->SetCanEverAffectNavigation(false);
	RootComponent = MeshComp;
	MovementForce = 400.f;
	RequiredDistanceToTarget = 100.f;
	DamageToSelf = 20;
	bUseVelocityChange = true;
	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	HealthComp->OnHealthChanged.AddDynamic(this, &ATrackerBot::OnHealthChanged);
	ExplosionDamage = 25.f;
	ExplosionRadius = 300.f;
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RangeOfContact = 100.f;
	SphereComp->SetSphereRadius(RangeOfContact);
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComp->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ATrackerBot::BeginPlay()
{
	Super::BeginPlay();
	NextPathPoint = GetNextPathPoint();
	MeshComp->AddForce(FVector(300, 0, 0) * MeshComp->GetMass() , NAME_None, bUseVelocityChange);
	
}

FVector ATrackerBot::GetNextPathPoint()
{
	//GetWorld()->GetFirstPlayerController()->;
	ACharacter* PlayerPawn = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	UNavigationPath* NavPath = UNavigationSystemV1::FindPathToActorSynchronously(GetWorld(), GetActorLocation(), PlayerPawn);
	if (NavPath->PathPoints.Num() > 1)
	{
		return NavPath->PathPoints[1];
	}
	return GetActorLocation();
}


// Called every frame
void ATrackerBot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float DistanceToTarget = (GetActorLocation() - NextPathPoint).Size();
	NextPathPoint = GetNextPathPoint();
	if (DistanceToTarget <= RequiredDistanceToTarget)
	{
		NextPathPoint = GetNextPathPoint();
		//DrawDebugString(GetWorld(), GetActorLocation(), "Target Reached");
	}
	else
	{
		FVector ForceDirection = NextPathPoint - GetActorLocation();
		ForceDirection.Normalize();
		ForceDirection *= MovementForce;
		// do targetu
		//DrawDebugDirectionalArrow(GetWorld(), GetActorLocation(), GetActorLocation() + ForceDirection, 40, FColor::Blue, false, 0.0f, 0, 1.0f);
		MeshComp->AddForce(ForceDirection, NAME_None, bUseVelocityChange);
		NextPathPoint = GetNextPathPoint();
	}
	
	//DrawDebugSphere(GetWorld(), NextPathPoint, 20, 12, FColor::Orange, false, 0.0f, 1.0f);
}

void ATrackerBot::OnHealthChanged(UHealthComponent* HealthComponent, float Health1, float HealthDelta, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	// Explode and push
	
	if (MaterialInstance == nullptr)
	{
		MaterialInstance = MeshComp->CreateAndSetMaterialInstanceDynamicFromMaterial(0, MeshComp->GetMaterial(0));
	}
	if (MaterialInstance)
	{
		MaterialInstance->SetScalarParameterValue("LastTimeDamageTaken", GetWorld()->TimeSeconds);
	}
	

	if (Health1 <= 0.f)
	{
		SelfDestruct();
	}
}

void ATrackerBot::SelfDestruct()
{
	if (bExploded)
	{
		return;
	}
	FVector explosionLocation = GetActorLocation();
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());
	TArray<AActor*> IgnoredActors;
	IgnoredActors.Add(this);
	bExploded = true;
	//SetActorLocation(FVector(0.f, 1000.f, 0.f));
	UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation());
	UGameplayStatics::ApplyRadialDamage(this, ExplosionDamage, explosionLocation, ExplosionRadius, nullptr, IgnoredActors, this, GetInstigatorController(), true);
	Destroy();
}

void ATrackerBot::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (!bStartedSelfDestruction)
	{
		ATracer_cppCharacter* PlayerPawn = Cast<ATracer_cppCharacter>(OtherActor);
		if (PlayerPawn)
		{
			UGameplayStatics::PlaySoundAtLocation(this, SelfDestructionTickingSound, GetActorLocation());
			GetWorldTimerManager().SetTimer(TimerHandle_LifeSpanExpired, this, &ATrackerBot::DamageSelf, 0.5f, true, 0.0f);
			bStartedSelfDestruction = true;
		}
	}
}

void ATrackerBot::DamageSelf()
{
	UGameplayStatics::ApplyDamage(this, DamageToSelf, GetInstigatorController(), this, nullptr);
}




