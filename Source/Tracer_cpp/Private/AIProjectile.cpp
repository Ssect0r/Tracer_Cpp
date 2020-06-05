// Fill out your copyright notice in the Description page of Project Settings.


#include "AIProjectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Tracer_cppCharacter.h"

// Sets default values
AAIProjectile::AAIProjectile()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	MeshComp->SetCanEverAffectNavigation(false);
	RootComponent = MeshComp;
	bUseVelocityChange = true;
	ExplosionDamage = 25.f;
	ExplosionRadius = 600.f;
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RangeOfContact = 100.f;
	SphereComp->SetSphereRadius(RangeOfContact);
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComp->SetupAttachment(RootComponent);
	timer = 0.f;
	InitalSpeed = 100;
	TimeToExplosion = 2.f;

}

// Called when the game starts or when spawned
void AAIProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called every frame
void AAIProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UGameplayStatics::SpawnEmitterAttached(FireEffect, this->GetDefaultAttachComponent());
	if (timer <= 0.2f)
	{
		ACharacter* ownerChar = Cast<ACharacter>(this->GetOwner());


		if (ownerChar)
		{
			FVector ForwardVector = ownerChar->GetActorForwardVector();
			
			FVector UpVector = ownerChar->GetActorUpVector();
			MeshComp->AddForce( ForwardVector  * MeshComp->GetMass() * InitalSpeed , NAME_None, bUseVelocityChange);
		}
		timer += DeltaTime;
	}
	if (timer <= TimeToExplosion)
	{
		timer += DeltaTime;
	}
	else
	{
		SelfDestruct();
	}


}


void AAIProjectile::SelfDestruct()
{
	if (bExploded)
	{
		return;
	}
	TSubclassOf<UDamageType> P;
	FVector explosionLocation = GetActorLocation();
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, explosionLocation);
	
	TArray<AActor*> IgnoredActors;
	IgnoredActors.Add(this);
	bExploded = true;
	UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation());
	UGameplayStatics::ApplyRadialDamage(this, ExplosionDamage, explosionLocation, ExplosionRadius, P, IgnoredActors, this, GetInstigatorController(), true);
	Destroy();
}

void AAIProjectile::NotifyActorBeginOverlap(AActor* OtherActor)
{
		ATracer_cppCharacter* PlayerPawn = Cast<ATracer_cppCharacter>(OtherActor);
		if (PlayerPawn)
		{
			UGameplayStatics::PlaySoundAtLocation(this, SelfDestructionTickingSound, GetActorLocation());

			SelfDestruct();
		}
	}
