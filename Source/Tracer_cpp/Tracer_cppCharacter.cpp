// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Tracer_cppCharacter.h"
#include "Tracer_cppProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "XRMotionControllerBase.h" // for FXRMotionControllerBase::RightHandSourceId
#include "CharacterAbilityManager.h"
#include "BaseAbility.h"
#include "Tracer_Ultimate.h"
#include "DrawDebugHelpers.h"
#include "Runtime/Engine/Classes/GameFramework/DamageType.h"
#include "Components/PawnNoiseEmitterComponent.h"
#include "HealthComponent.h"
#include "Runtime/Engine/Classes/GameFramework/PawnMovementComponent.h"
#include "CharacterTalentTree.h"
#include "MyGameInstance.h"
#include "Particles/ParticleSystemComponent.h"





DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// ATracer_cppCharacter

ATracer_cppCharacter::ATracer_cppCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	AbilityManager = CreateDefaultSubobject<UCharacterAbilityManager>(TEXT("CharacterAbilityManager"));
	AbilityManager->setCharacter(this);

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	FP_Gun->SetupAttachment(RootComponent);

	//SECOND WEAPON
	FP_Gun2 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun2"));
	FP_Gun2->SetOnlyOwnerSee(true);
	FP_Gun2->bCastDynamicShadow = false;
	FP_Gun2->CastShadow = false;
	FP_Gun2->SetupAttachment(RootComponent);

	FP_MuzzleLocationL = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocationL->SetupAttachment(FP_Gun);
	FP_MuzzleLocationL->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	//SECOND WEAPON
	FP_MuzzleLocationR = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation2"));
	FP_MuzzleLocationR->SetupAttachment(FP_Gun2);
	FP_MuzzleLocationR->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	GetCapsuleComponent()->SetCollisionResponseToChannel( ECollisionChannel::ECC_WorldDynamic,ECR_Ignore); // zeby mesh tylko przyjmowal hit, jeszcze sprawdzic GameTraceChannel1
	BulletSpread = 20.0f;


	// WIDGET
	GunOffset = FVector(100.0f, 0.0f, 10.0f);

	NoiseEmitterComponent = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("NoiseEmitter"));
	ReloadProgress = 0.f;
	
	//HEALTHCOMPONENT
	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComp"));

	GetMesh()->SetGenerateOverlapEvents(true);
	Mesh1P->SetGenerateOverlapEvents(true);
	TalentTree = CreateDefaultSubobject<UCharacterTalentTree>(TEXT("CharacterTalentTree"));
	PlayerTag.SetNumber(0);
	
}

void ATracer_cppCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	TalentTree->GainSkillPoint();
	HealthComp->OnHealthChanged.AddDynamic(this, &ATracer_cppCharacter::OnHealthChanged);
	GI = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	GI->SetStartingValuesFromSaveData();
	
	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	FP_Gun2->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPointL"));
	TraceTargetName = "Target";
	CurrentLevelName = "";
	CurrentLevelName.Append(basic);
	CurrentLevelName.Append(FString::FromInt(GI->GetLevelNumber() + 1));
	CurrentLevelName;
}

void ATracer_cppCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATracer_cppCharacter::OnFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ATracer_cppCharacter::OffFire);

	// Bind skill event
	PlayerInputComponent->BindAction("FirstAbility", IE_Pressed, this, &ATracer_cppCharacter::UseFirstAbility);
	PlayerInputComponent->BindAction("SecondAbility", IE_Pressed, this, &ATracer_cppCharacter::UseSecondAbility);
	PlayerInputComponent->BindAction("UltimateAbility", IE_Pressed, this, &ATracer_cppCharacter::UseUltimateAbility);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ATracer_cppCharacter::Reload);
	PlayerInputComponent->BindAction("ShowTalentSystem", IE_Pressed, this, &ATracer_cppCharacter::ShowTalentSystem);
	PlayerInputComponent->BindAction("TestTalentSystem", IE_Pressed, this, &ATracer_cppCharacter::TestTalentSystem);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &ATracer_cppCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATracer_cppCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

void ATracer_cppCharacter::SetKillsToFinishLevel(int kills)
{
	KillsToFinishLevel += kills;
}

void ATracer_cppCharacter::SetDamageToFinishLevel(float damage)
{
	DamageToFinishLevel += damage;
}

void ATracer_cppCharacter::KillCountIncrease()
{
	KillsProgressToFinishLevel++;
}

float ATracer_cppCharacter::GetBlinkCooldown()
{
	float cooldown = AbilityManager->FirstAbilityCooldown;
	return cooldown;
}

int ATracer_cppCharacter::GetSkillpointSpended()
{
	int Points = TalentTree->SkillPointsSpended;
	return Points;
}

void ATracer_cppCharacter::SetSkillPointToSpend(int SkillPoints)
{
	TalentTree->SkillPoints = SkillPoints;
}

int ATracer_cppCharacter::GetSkillPointToSpend()
{
	int Points = TalentTree->SkillPoints;
	return Points;
}

void ATracer_cppCharacter::UseFirstAbility()
{
	AbilityManager->UseAbility(EAbilityType::PRIMARY);
}

void ATracer_cppCharacter::UseSecondAbility()
{
	if (AbilityManager->GetSecondAbilityHealFlag())
	{
		HealthComp->Heal();
		
	}
	AbilityManager->UseAbility(EAbilityType::SECONDARY);
}

void ATracer_cppCharacter::UseUltimateAbility()
{
	AbilityManager->UseAbility(EAbilityType::ULTIMATE);
	if (AbilityManager->bIsAbleToRestartDamageCounter())
	{
		DamageProgressToFinishLevel = 0;
	}
}

void ATracer_cppCharacter::Reload()
{
	isAbleToShoot = false;
}

bool ATracer_cppCharacter::AddChangesFromTalents(class UBaseTalent* TalentClass)
{
	int Talent = TalentTree->CheckTalentClass(TalentClass);
	//TalentTree->TalentsUnderChange = true;
	if (Talent == 1)
	{
		if (TalentTree->SpendSkillPoint())
		{
			PlayerPistolDamage += TalentTree->GetProjectileDamage();
		return true;
		}
		else
		{
			return false;
		}
	}
	if (Talent == 2)
	{
		if (TalentTree->SpendSkillPoint())
		{
			rateOfFire *= TalentTree->GetFireRate();
			return true;
		}
		else
		{
			return false;
		}
	}
	if (Talent == 3)
	{
		if (TalentTree->SpendSkillPoint())
		{
		BulletSpread -= TalentTree->GetWeaponSpreadDecrease();
		return true;
		}
		else
		{
			return false;
		}
	}
	if (Talent == 4)
	{
		if (TalentTree->SpendSkillPoint())
		{
		ReloadTime -= TalentTree->GetReloadTimeDecrease();
		return true;
		}
		else
		{
			return false;
		}
	}
	if (Talent == 5)
	{
		if(TalentTree->SpendSkillPoint())
		{
		AmmoCapacity += TalentTree->GetAmmoCapacityIncrease();
		return true;
		}
		else
		{
			return false;
		}
	}
	if (Talent == 6)
	{
		if (TalentTree->SpendSkillPoint())
		{
		AbilityManager->lvlupFirstAbility(TalentTree->GetBlinkCooldownReduction());
		return true;
		}
		else
		{
			return false;
		}
	}
	if (Talent == 7)
	{
		if (TalentTree->SpendSkillPoint())
		{
		AbilityManager->lvlupSecondAbility(TalentTree->GetSecondAbilityCooldownReduction());
		return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}

	//TalentTree->TalentsUnderChange = false;
}

void ATracer_cppCharacter::ReloadComplete()
{
	ActualAmmo = AmmoCapacity;
	ReloadProgress = 0.f;
	isAbleToShoot = true;
}

int ATracer_cppCharacter::GetAmmoCapacity()
{
	return AmmoCapacity;
}

int ATracer_cppCharacter::GetActualAmmo()
{
	return ActualAmmo;
}

float ATracer_cppCharacter::UltimateProgress()
{
	float Progress = DamageProgressToFinishLevel / DamageToFinishLevel;
	if (Progress >= 1)
	{
		AbilityManager->SetUltimateSpecialFlagReady();
	}
	return Progress;
}


void ATracer_cppCharacter::TestTalentSystem()
{
	//UE_LOG(LogTemp, Warning, TEXT("Talent"));
	//PlayerPistolDamage *= TalentTree->GetProjectileDamage();
	//UE_LOG(LogTemp, Warning, TEXT("PistolDmg: %f"),PlayerPistolDamage);
	//rateOfFire *= TalentTree->GetFireRate();
	//UE_LOG(LogTemp, Warning, TEXT("rateOfFire: %f"),rateOfFire);
	//BulletSpread -= TalentTree->GetWeaponSpreadDecrease();
	//UE_LOG(LogTemp, Warning, TEXT("BulletSpread: %f"), BulletSpread);
	//ReloadTime -= TalentTree->GetReloadTimeDecrease();
	//AmmoCapacity += TalentTree->GetAmmoCapacityIncrease();
	//AbilityManager->lvlupFirstAbility(TalentTree->GetBlinkCooldownReduction());
	//AbilityManager->lvlupSecondAbility(TalentTree->GetSecondAbilityCooldownReduction());
}

int ATracer_cppCharacter::GetActualHP()
{
	return HealthComp->getHP();
}

FText ATracer_cppCharacter::GetAmmoCapacityIntText()
{
	FString AmmoString = FString::FromInt(AmmoCapacity);
	FText AmmoText = FText::FromString(AmmoString);
	return AmmoText;
}

void ATracer_cppCharacter::SetTalentTreeDefaultValues()
{
	GI->SetStartingValues();
}

FText ATracer_cppCharacter::GetActualAmmoIntText()
{
	FString ActualAmmoString = FString::FromInt(ActualAmmo);
	FText ActualAmmoText = FText::FromString(ActualAmmoString);
	return ActualAmmoText;
}

void ATracer_cppCharacter::OnHealthChanged(UHealthComponent* HealthComponent, float Health1, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCause)
{
	//UE_LOG(Log)
	if (Health1 <= 0.0f && !HealthComponent->isDead())
	{
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
		UWorld* TheWorld = GetWorld();
		//FString CurrentLevelName = TheWorld->GetMapName().RightChop(9);
		CurrentLevelName = GI->GetSActualLevelToRestart();
		FName CurrentLevel = *CurrentLevelName;
		GetMovementComponent()->StopMovementImmediately();
		HealthComponent->bDied = true;
		bDied = true;
		SetLifeSpan(5.f);
		Mesh1P->SetVisibility(false);
		HealthComponent->setDead();
		UGameplayStatics::OpenLevel(TheWorld, CurrentLevel);
	}
}

void ATracer_cppCharacter::OnFire()
{
	isShooting = true;
	// try and fire a projectile
}
void ATracer_cppCharacter::OffFire()
{
	isShooting = false;
}

void ATracer_cppCharacter::AutomaticShooting(bool isShooting, float time)
{
	if (isShooting)
	{
		if (rateOfFireTemp >= rateOfFire)
		{
			if (ProjectileClass != NULL)
			{
				if (isAbleToShoot)
				{
					MakeNoise(15.0f, Instigator, this->GetActorLocation());
					const FRotator SpawnRotation = GetControlRotation();
					// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
					if (isFirstGunShotLast == true)
					{
						Shoot(FP_MuzzleLocationL);
						//const FVector SpawnLocationL = ((FP_MuzzleLocationL != nullptr) ? FP_MuzzleLocationL->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);
						isFirstGunShotLast = false;
						rateOfFireTemp = 0.f;
					}
					else if (isFirstGunShotLast == false)
					{
						Shoot(FP_MuzzleLocationR);
						//const FVector SpawnLocationR = ((FP_MuzzleLocationR != nullptr) ? FP_MuzzleLocationR->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);
						isFirstGunShotLast = true;
						rateOfFireTemp = 0.f;
					}
				}
			}
			// try and play the sound if specified
			if (FireSound != NULL && isAbleToShoot)
			{
				UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
			}
			// try and play a firing animation if specified
			if (FireAnimation != NULL && isAbleToShoot)
			{
				// Get the animation object for the arms mesh
				UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
				if (AnimInstance != NULL)
				{
					AnimInstance->Montage_Play(FireAnimation, 1.f);
				}
			}
		}
		else {
			rateOfFireTemp += time;
		}
	}
}

void ATracer_cppCharacter::Shoot(USceneComponent* muzzle)
{
	UWorld* const World = GetWorld();
	if (World != NULL)
	{
		const FRotator SpawnRotation = GetControlRotation();
		const FVector SpawnLocation = ((muzzle != nullptr) ? muzzle->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

		FVector ForwardVector = FirstPersonCameraComponent->GetForwardVector();

		float HalfRad = FMath::DegreesToRadians(BulletSpread);
		ForwardVector = FMath::VRandCone(ForwardVector, HalfRad, HalfRad);

		FActorSpawnParameters ActorSpawnParams;
		FHitResult hit;
		FVector bulletDestinationLocation = ((ForwardVector * 1050.f) + SpawnLocation);
		FCollisionQueryParams collisionParams(FCollisionQueryParams::DefaultQueryParam);
		TSubclassOf<UDamageType> P;
		ActorSpawnParams.Instigator = this;
		bool isHit = GetWorld()->LineTraceSingleByChannel(hit, SpawnLocation, bulletDestinationLocation, ECC_Pawn,collisionParams);
		if (isHit)
		{
			UE_LOG(LogTemp, Warning, TEXT("HIT"));
			if (hit.bBlockingHit)
			{
				BulletDestination = hit.ImpactPoint;
				bulletDestinationLocation = hit.Location;
				AActor* bullet = World->SpawnActor<ATracer_cppProjectile>(ProjectileClass, GetActorLocation(), SpawnRotation, ActorSpawnParams);
				if (hit.GetActor() != nullptr) {
					if (hit.Actor.Get()->bCanBeDamaged)
					{
						UGameplayStatics::ApplyPointDamage(hit.GetActor(), PlayerPistolDamage, this->GetActorLocation(), hit, nullptr, this, P);
						DamageProgressToFinishLevel += PlayerPistolDamage;
					}
					if (TraceEffect)
					{
						FVector Location = FP_MuzzleLocationL->GetComponentLocation();
						UParticleSystemComponent* TraceComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TraceEffect, SpawnLocation);
						if (TraceComp)
						{
							TraceComp->SetVectorParameter("BeamEnd", BulletDestination);
						}
					}
				}
			}
		}
		ActualAmmo--;
		if (ActualAmmo == 0)
		{
			isAbleToShoot = false;
		}
	}
}

void ATracer_cppCharacter::Tick(float DeltaSeconds)
{
	AutomaticShooting(isShooting, DeltaSeconds);

	if (!isAbleToShoot)
	{
		if (ReloadProgress <= ReloadTime)
		{
			ReloadProgress += DeltaSeconds;
		}
		else
		{
			ReloadComplete();
		}
	}
	/*if (DamageProgressToFinishLevel >= DamageToFinishLevel)
	{
		
		GI->SetTalentSaveData();
		UWorld* TheWorld = GetWorld();

		FString CurrentLevel = TheWorld->GetMapName();

	
					UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("Level_02")));

	}*/
	if (KillsProgressToFinishLevel >= KillsToFinishLevel)
	{
	    CurrentLevelName = "";
		CurrentLevelName.Append(basic);
		CurrentLevelName.Append(FString::FromInt(GI->GetLevelNumber() +1));
		FName CurrentLevel = *CurrentLevelName;
		GI->SetActualLevelToRestart(CurrentLevelName);
		GI->SetTalentSaveData();
		UWorld* TheWorld = GetWorld();
		
		//FString CurrentLevel = TheWorld->GetMapName();
		if (CurrentLevel == "Level_1")
		{
			GI->SetKillsToEnd(2);

		}
		if (CurrentLevel == "Level_10")
		{
			GI->SetKillsToEnd(1);
			
		}
		if (CurrentLevel == "Level_11")
		{

			GI->ResetLevelNumber();
			GI->SetStartingValues();
			GI->SetKillsToEnd(2);
		}
			UGameplayStatics::OpenLevel(TheWorld, FName(CurrentLevel));
	}
}



void ATracer_cppCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
		MakeNoise(2.0f, Instigator, this->GetActorLocation());
	}
}

void ATracer_cppCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
		MakeNoise(2.0f, Instigator, this->GetActorLocation());
	}
}


