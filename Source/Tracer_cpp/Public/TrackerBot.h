// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TrackerBot.generated.h"

UCLASS()
class TRACER_CPP_API ATrackerBot : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATrackerBot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UFUNCTION()
	FVector GetNextPathPoint();


	FVector NextPathPoint;

	UPROPERTY(EditAnywhere, Category = "AI")
	float MovementForce;

	UPROPERTY(EditAnywhere, Category = "AI")
	bool bUseVelocityChange;

	UPROPERTY(EditAnywhere, Category = "AI")
	float RequiredDistanceToTarget;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	class UHealthComponent* HealthComp;

	UMaterialInstanceDynamic* MaterialInstance;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	bool bDied;

	UFUNCTION()
	void OnHealthChanged(UHealthComponent* HealthComponent, float Health1, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION()
	void SelfDestruct();

	UPROPERTY(EditDefaultsOnly, Category = "TrackerBot")
	UParticleSystem* ExplosionEffect;

	UPROPERTY(EditDefaultsOnly, Category = "TrackerBot")
	float ExplosionDamage;

	UPROPERTY(EditDefaultsOnly, Category = "TrackerBot")
		float DamageToSelf;

	UPROPERTY(EditDefaultsOnly, Category = "TrackerBot")
	float ExplosionRadius;

	UPROPERTY(EditDefaultsOnly, Category = "TrackerBot")
	float RangeOfContact;

	UPROPERTY(EditDefaultsOnly, Category = "TrackerBot")
	bool bExploded = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* ExplosionSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* HitSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* SpawnSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* SelfDestructionTickingSound;

	UPROPERTY(EditAnywhere, Category = "TrackerBot")
	class USphereComponent* SphereComp;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	FTimerHandle TimerHandle_SelfDamage;

	void DamageSelf();

	bool bStartedSelfDestruction;
};
