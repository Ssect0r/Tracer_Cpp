// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterTalentTree.generated.h"

/**
 * 
 */
//enum class ETalentType : int
//{
//	PROJECTILEDAMAGE=1,
//	FIRERATE,
//	SPREAD,
//	RELOADTIME,
//	AMMOCAPACITY,
//	BLINKCOOLDOWN,
//	SECONDABILITYCOOLDOWN
//};

UCLASS()
class TRACER_CPP_API UCharacterTalentTree : public UActorComponent
{
	GENERATED_BODY()

public:
	UCharacterTalentTree();

	UPROPERTY(VisibleAnywhere, Category = "Talent")
	class UBaseTalent* ProjectileDamageTalent1;

	UPROPERTY(VisibleAnywhere, Category = "Talent")
	class UBaseTalent* FireRateTalent;

	UPROPERTY(VisibleAnywhere, Category = "Talent")
	class UBaseTalent* WeaponSpreadTalent;

	UPROPERTY(VisibleAnywhere, Category = "Talent")
	class UBaseTalent* ReloadTimeTalent;

	UPROPERTY(VisibleAnywhere, Category = "Talent")
	class UBaseTalent* AmmoCapacityTalent;

	UPROPERTY(VisibleAnywhere, Category = "Talent")
	class UBlinkCooldownReductionTalent* BlinkCooldownReductionTalent;

	class USecondAbilityCooldownTalent* SecondAbilityCooldownTalent;

	UPROPERTY(VisibleAnywhere, Category = "Talent")
	TArray<UBaseTalent*> TalentArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TalentTree")
	int SkillPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TalentTree")
	bool TalentsUnderChange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TalentTree")
	int SkillPointsSpended;

	UFUNCTION()
	void GainSkillPoint();

	UFUNCTION()
	bool SpendSkillPoint();

	UFUNCTION()
	float GetProjectileDamage();

	UFUNCTION()
	float GetFireRate();

	UFUNCTION()
	float GetWeaponSpreadDecrease();

	UFUNCTION()
	float GetReloadTimeDecrease();

	UFUNCTION()
	float GetAmmoCapacityIncrease();

	UFUNCTION()
	float GetBlinkCooldownReduction();

	UFUNCTION()
	float GetSecondAbilityCooldownReduction();

	UFUNCTION()
	int CheckTalentClass(UBaseTalent* ClassType);

	UFUNCTION()
	int GetSkillPointsSpended();

	UFUNCTION()
	int GetProjectileDamageTalentRank();

	UFUNCTION()
	bool GetProjectileDamageTalentbLock();

	UFUNCTION()
	int GetFireRateTalentRank();

	UFUNCTION()
	bool GetFireRateTalentTalentbLock();

	UFUNCTION()
	int GetSpreadTalentRank();

	UFUNCTION()
	bool GetSpreadTalentTalentbLock();
	
	UFUNCTION()
	int GetReloadTimeTalentRank();

	UFUNCTION()
	bool GetReloadTimeTalentbLock();

	UFUNCTION()
	int GetAmmoCapacityTalentRank();

	UFUNCTION()
	bool GetAmmoCapacityTalentbLock();

	UFUNCTION()
	int GetBlinkCooldownTalentRank();

	UFUNCTION()
	bool GetBlinkCooldownTalentbLock();

	UFUNCTION()
	int GetRewindCooldownTalentRank();

	UFUNCTION()
	bool GetRewindCooldownTalentbLock();




	UFUNCTION()
	void SetProjectileDamageTalent(int rank, bool bLock);

	UFUNCTION()
	void SetFireRateTalent(float rank, bool bLock);

	UFUNCTION()
	void SetSpreadTalent(float rank, bool bLock);

	UFUNCTION()
	void SetReloadTimeTalent(float rank, bool bLock);

	UFUNCTION()
	void SetAmmoCapacityTalent(float rank, bool bLock);

	UFUNCTION()
	void SetBlinkCooldownTalent(float rank, bool bLock);

	UFUNCTION()
	void SetRewindCooldownTalent(float rank, bool bLock);

	UFUNCTION(BlueprintCallable, Category = "TalentTree")
	void RefreshTalents();

	UFUNCTION(BlueprintCallable, Category = "TalentTree")
		bool CheckSkillPoints();



	UFUNCTION(BlueprintPure, Category = "TalentTree")
	FORCEINLINE TArray<UBaseTalent*> GetTalentArray() { return TalentArray; }

	
protected:
	virtual void BeginPlay() override;

	UBaseTalent* LookForTalentInArray(UClass* ClassParameter);
	
	
	
};
