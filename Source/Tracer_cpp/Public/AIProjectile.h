// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AIProjectile.generated.h"

UCLASS()
class TRACER_CPP_API AAIProjectile : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAIProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		UStaticMeshComponent* MeshComp;

	FVector NextPathPoint;

	float timer;

	UPROPERTY(EditAnywhere, Category = "AI")
		bool bUseVelocityChange;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void SelfDestruct();

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
		UParticleSystem* ExplosionEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
		UParticleSystem* FireEffect;

		UPROPERTY(VisibleAnywhere, Category = "Health")
		class UHealthComponent* HealthComp;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
		float ExplosionDamage;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
		float ExplosionRadius;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
		float RangeOfContact;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
		bool bExploded = false;

	UPROPERTY(EditAnywhere, Category = "Projectile")
		float InitalSpeed;

	UPROPERTY(EditAnywhere, Category = "Projectile")
		float TimeToExplosion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* ExplosionSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* HitSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* SpawnSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* SelfDestructionTickingSound;

	UPROPERTY(EditAnywhere, Category = "Projectile")
		class USphereComponent* SphereComp;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;





};
