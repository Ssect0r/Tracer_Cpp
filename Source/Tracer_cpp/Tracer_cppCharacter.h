// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Components/TimelineComponent.h"
#include "Components/BoxComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Tracer_cppCharacter.generated.h"


//class UInputComponent;

UCLASS(config=Game)
class ATracer_cppCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	class USkeletalMeshComponent* Mesh1P;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FP_Gun;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FP_Gun2;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* FP_MuzzleLocationL;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* FP_MuzzleLocationR;

	/** Gun mesh: VR view (attached to the VR controller directly, no arm, just the actual gun) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* VR_Gun;

	/** Location on VR gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* VR_MuzzleLocation;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(VisibleAnywhere, Category = "Ability")
	class UCharacterAbilityManager* AbilityManager;

	UPROPERTY(VisibleAnywhere, Category = Gameplay)
	class UPawnNoiseEmitterComponent* NoiseEmitterComponent;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	class UHealthComponent* HealthComp;

	UPROPERTY(VisibleAnywhere, Category = "TalentTree")
	class UCharacterTalentTree* TalentTree;

public:
	ATracer_cppCharacter();

protected:
	virtual void BeginPlay();

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category = "Ammo")
	int AmmoCapacity = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		int KillCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelChange")
	float DamageProgressToFinishLevel = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelChange")
		int KillsProgressToFinishLevel = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelChange")
		int LevelNumber = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelChange")
	float DamageToFinishLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelChange")
		float KillsToFinishLevel = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	int ActualAmmo = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	float ReloadTime = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		FVector BulletDestination;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	float ReloadProgress;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		UParticleSystem* TraceEffect;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		FName TraceTargetName;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TalentTree")
	float PlayerPistolDamage;

	UPROPERTY()
	class UMyGameInstance* GI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	float rateOfFire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	float rateOfFireTemp = 0.f;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	//int health = 100;

	bool isAbleToShoot = true;
	bool isFirstGunShotLast = true;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector GunOffset;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class ATracer_cppProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ATracer_Ultimate> UltimateProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation;

	UPROPERTY(BlueprintReadOnly, Category = "Player")
	bool bDied;

	UPROPERTY(BlueprintReadOnly, Category = "Player")
	FName PlayerTag;

	UPROPERTY(EditAnywhere, Category = "Player", meta = (ClampMin = 0.0f))
	float BulletSpread;

	UFUNCTION(BlueprintPure, Category = "TalentTree")
	FORCEINLINE UCharacterTalentTree* GetTalentTree() { return TalentTree; }



protected:
	
	/** Fires a projectile. */
	void OnFire();
	void OffFire();
	bool isShooting = false;


	void AutomaticShooting(bool isShooting, float time);

	FString basic = "Level_";
	FString CurrentLevelName = "";

	void Shoot(USceneComponent* muzzle);

	UFUNCTION(BlueprintCallable,Category = "Ammo" )
	void Reload();

	UFUNCTION(BlueprintCallable, Category = "Talent")
	bool AddChangesFromTalents(class UBaseTalent* TalentClass);

	UFUNCTION()
	void ReloadComplete();

	UFUNCTION(BlueprintPure, Category = "Ammo")
	int GetAmmoCapacity();

	UFUNCTION(BlueprintPure, Category = "Ammo")
	int GetActualAmmo();
	
	UFUNCTION(BlueprintCallable, Category = "AbilityManager")
	float UltimateProgress();

	UFUNCTION(BlueprintImplementableEvent, Category = "TalentSystem")
	void ShowTalentSystem();

	UFUNCTION()
	void TestTalentSystem();



	UFUNCTION(BlueprintPure, Category = "Health")
	int GetActualHP();

	//UFUNCTION(BlueprintCallable, Category = "Health")
	//void GetDamage();

	//UFUNCTION(BlueprintCallable, Category = "Health")
	//void SetHealth(float hp);

	UFUNCTION(BlueprintPure, Category = "Ammo")
	FText GetAmmoCapacityIntText();

	UFUNCTION(BlueprintPure, Category = "Ammo")
	FText GetActualAmmoIntText();

	UFUNCTION()
	void OnHealthChanged(UHealthComponent* HealthComponent, float Health1, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	void UseFirstAbility();
	void UseSecondAbility();
	void UseUltimateAbility();

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "GameInstance")
	void SetTalentTreeDefaultValues();
	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	UFUNCTION(BlueprintCallable, Category = "Progress")
	FORCEINLINE float GetDamageProgressToFinishLevel() { return DamageProgressToFinishLevel; }

	UFUNCTION(BlueprintCallable, Category = "Progress")
		FORCEINLINE float GetDamageToFinishLevel() { return DamageToFinishLevel; }

	UFUNCTION(BlueprintCallable, Category = "Progress")
		FORCEINLINE float GetKillsToFinishLevel() { return KillsToFinishLevel; }

	UFUNCTION()
		void SetKillsToFinishLevel(int kills);

	UFUNCTION()
		void SetDamageToFinishLevel(float damage);

	UFUNCTION()
		void KillCountIncrease();

	UFUNCTION(BlueprintPure, Category = "Ability")
	FORCEINLINE UCharacterAbilityManager* GetAbilityManager() { return AbilityManager; }

	UFUNCTION(BlueprintPure, Category = "Ability")
	float GetBlinkCooldown();

	UFUNCTION(BlueprintPure, Category = "Ability")
	int GetSkillpointSpended();

	UFUNCTION(BlueprintPure, Category = "Ability")
	int GetSkillPointToSpend();

	UFUNCTION()
	void SetSkillPointToSpend(int skillPoints);




};

