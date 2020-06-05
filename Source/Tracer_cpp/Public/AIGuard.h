// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIGuard.generated.h"

class UPawnSensingComponent;

UCLASS()
class TRACER_CPP_API AAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIGuard();

	//UPROPERTY(VisibleAnywhere, Category = "Components")
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool bTargetInSight = false;

	float SpreadTime = 0.f;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnSensingComponent* PawnSensingComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	class UBoxComponent* OverlapCheckArea;

	UPROPERTY(EditInstanceOnly, Category = "Patrol")
	AActor* FirstPatrolPoint;

	UPROPERTY(EditAnywhere, Category = "Patrol")
	bool bIsAbleToPatrol = false;

	UPROPERTY(EditInstanceOnly, Category = "Patrol")
	AActor* SecondPatrolPoint;

	UPROPERTY(EditInstanceOnly, Category = "Patrol")
	bool shouldPatrol = false;

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	bool bDied;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	class UHealthComponent* HealthComp;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FP_Gun;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector GunOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	float BulletSpread = 40;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	float RangeOfBullets = 1050.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	float BulletDamage= 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	float HPToRetreat= 20.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	bool bIsAbleToRetreat = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	bool bShouldRetreat = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	bool bAbleToStop = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* ShootSound;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		float RangeOfShooting;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		float RangeOfFollow;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		bool bIsSummoned;


	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ATracer_cppProjectile> ProjectileClass;


	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* FP_MuzzleLocationL;

	AActor* CurrentPatrolPoint;

	UFUNCTION()
	void Shoot(USceneComponent* muzzle);

	UFUNCTION()
	virtual void OnPawnSeen(APawn* SeenPawn);

	UFUNCTION()
	void RetreatEnemySeen();


	UPROPERTY()
	bool bShooting = false;

	UPROPERTY()
	bool bSpread = false;

	UFUNCTION()
	void Patrol();

	UFUNCTION()
	virtual void OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume);

	UFUNCTION()
	void OnHealthChanged(UHealthComponent* HealthComponent, float Health1, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	FRotator OriginalOrientation;
	FVector OriginalLocation;

	void ResetOrientation();

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	FTimerHandle TimerHandle_ResetOrientation;
	FTimerDelegate* TimerDelegate_ResetOrientation;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* SpawnSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		UParticleSystem* TraceEffect;


	UFUNCTION()
		void SetbIsSummoned(bool bSummoned);

};
