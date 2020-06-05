// Fill out your copyright notice in the Description page of Project Settings.


#include "Tracer_Ultimate.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ATracer_Ultimate::ATracer_Ultimate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &ATracer_Ultimate::OnHit);		// set up a notification for when this component hits something blocking
	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;
	CollisionComp->SetGenerateOverlapEvents(true);
	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	UStaticMeshComponent* mesh = Cast<UStaticMeshComponent>(this->GetRootComponent());
	if (mesh)
	{
		mesh->SetMassOverrideInKg(NAME_None, 0.f);
	}
	IgnoredActors.Add(this);
	// Die after 3 seconds by default
	//InitialLifeSpan = 3.0f;

}

// Called when the game starts or when spawned
void ATracer_Ultimate::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::PlaySoundAtLocation(this, SpawnSound, GetActorLocation());
	
}

// Called every frame
void ATracer_Ultimate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	timeToExplode += DeltaTime;
	if (isAttached)
	{
		AttachedBombLogic(timeToExplode, explosionRadius, isAttached);
	}
	else if (!isAttached && this->GetVelocity() == FVector(0, 0, 0)) {
		LandedBombLogic(timeToExplode, bombRadius, isAttached);
	}
}


void ATracer_Ultimate::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	MakeNoise(1.0f, Instigator, this->GetActorLocation());
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{	
		isAttached = true;
		this->SetObjectToAttach(OtherActor);
		UStaticMeshComponent* mesh = Cast<UStaticMeshComponent>(this->GetRootComponent());
		OtherComp->SetSimulatePhysics(false);
		if (mesh)
		{
			HitComp->SetSimulatePhysics(false);
		}
		this->AttachToActor(OtherActor,FAttachmentTransformRules::KeepWorldTransform);
		OtherComp->SetSimulatePhysics(true);
	}
}


	void ATracer_Ultimate::SetObjectToAttach(AActor* OtherActor)
	{
		this->ActorToAttach = OtherActor;
	}



	void ATracer_Ultimate::AttachedBombLogic(float time, float radius, bool isAttached)
	{
		MakeNoise(1.0f, Instigator, this->GetActorLocation());
		TArray<FHitResult> outHits;
		FVector bombLocation = this->GetActorLocation();
		FCollisionShape explosionSphere = FCollisionShape::MakeSphere(radius);
		bool isHit = GetWorld()->SweepMultiByChannel(outHits, bombLocation, bombLocation + FVector(1, 1, 1), FQuat::Identity, ECollisionChannel::ECC_WorldDynamic, explosionSphere);
		DrawDebugSphere(GetWorld(), bombLocation, explosionSphere.GetSphereRadius(), 10, FColor::Cyan);
		if (isHit)
		{
			for (auto& hit : outHits)
			{
				if (hit.GetActor() && hit.GetActor()->GetRootComponent())
				{
					UStaticMeshComponent* mesh = Cast<UStaticMeshComponent>((hit.GetActor()->GetRootComponent()));
					if (mesh)
					{
						if (timeToExplode >= timeOfExplosion)
						{
							UGameplayStatics::ApplyRadialDamage(this, 500, bombLocation, explosionRadius, nullptr, IgnoredActors, this, GetInstigatorController(), true);
							mesh->AddRadialImpulse(bombLocation, explosionSphere.GetSphereRadius(), 5000.f, ERadialImpulseFalloff::RIF_Constant, true);
							UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation());
							UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());
							this->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
							if (this)
							{
								Destroy();
							}
						}
					}
				}
			}
		}
	}

	void ATracer_Ultimate::LandedBombLogic(float time, float radius, bool isAttached)
	{
		MakeNoise(1.0f, Instigator, this->GetActorLocation());
		TArray<FHitResult> outHits;
		FVector bombLocation = this->GetActorLocation();
		FCollisionShape explosionSphere = FCollisionShape::MakeSphere(radius);



		bool isHit = GetWorld()->SweepMultiByChannel(outHits, bombLocation, bombLocation + FVector(1, 1, 1), FQuat::Identity, ECollisionChannel::ECC_WorldDynamic, explosionSphere);

		DrawDebugSphere(GetWorld(), bombLocation, explosionSphere.GetSphereRadius(), 10, FColor::Cyan);

		if (isHit)
		{
			for (auto& hit : outHits)
			{
				if (hit.GetActor() && hit.GetActor()->GetRootComponent() != nullptr)
				{
					UStaticMeshComponent* mesh = Cast<UStaticMeshComponent>((hit.GetActor()->GetRootComponent()));
						if (!isAttached && hit.GetActor()->GetRootComponent()->HasBegunPlay()) //&& this->GetDistanceTo(hit.GetActor()) > 300.f)
						{
							this->AttachToActor(hit.GetActor(), FAttachmentTransformRules::KeepWorldTransform);
							isAttached = true;
							AttachedBombLogic(time, explosionRadius, isAttached);
						}

						else if (!isAttached && hit.GetActor() && hit.GetActor()->GetRootComponent() != nullptr && time >=timeOfExplosion)
						{
							ExplodeWithoutAttach(time, explosionRadius);
						}
				}
			}
		}
	}

	void ATracer_Ultimate::ExplodeWithoutAttach(float time, float radius)
	{
		TArray<FHitResult> outHits;
		FVector bombLocation = this->GetActorLocation();
		FCollisionShape explosionSphere = FCollisionShape::MakeSphere(radius);
		
		MakeNoise(1.0f, Instigator, this->GetActorLocation());
		bool isHit = GetWorld()->SweepMultiByChannel(outHits, bombLocation, bombLocation + FVector(1, 1, 1), FQuat::Identity, ECollisionChannel::ECC_WorldDynamic, explosionSphere);
		DrawDebugSphere(GetWorld(), bombLocation, explosionSphere.GetSphereRadius(), 10, FColor::Cyan);
		if (isHit)
		{
			for (auto& hit : outHits)
			{
				if (hit.GetActor() && hit.GetActor()->GetRootComponent() != nullptr)
				{
					UStaticMeshComponent* mesh = Cast<UStaticMeshComponent>((hit.GetActor()->GetRootComponent()));

						if (mesh)
						{
							UGameplayStatics::ApplyRadialDamage(this, 500, bombLocation, explosionRadius, nullptr, IgnoredActors, this, GetInstigatorController(), true);
							mesh->AddRadialImpulse(bombLocation, explosionRadius, 5000.f, ERadialImpulseFalloff::RIF_Constant, true);
							UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation());
							UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());
							this->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
							if (this)
							{
								Destroy();
							}
						}
				}
			}
		}
	}
	
