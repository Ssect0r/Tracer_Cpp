// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/ActorComponent.h"
#include "AIAbilityManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRACER_CPP_API UAIAbilityManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAIAbilityManager();

	UPROPERTY()
	ACharacter* character;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UPROPERTY(EditAnywhere, Category = "AIAbilities")
	TArray<TSubclassOf<class UAIBaseAbility>> AbilityArray;

	UFUNCTION()
	UAIBaseAbility* FindAbilityFunction(int Index);

	UFUNCTION()
		void SpawnTracker();

	UFUNCTION()
		void SpawnGuard();

	UFUNCTION()
		void SpawnMage();

	UFUNCTION()
		void SpawnRotatingOrb();
	   
	UFUNCTION()
		void SpawnFireBall();

	UFUNCTION()
		void SpawnBouncingFireBall();

	UFUNCTION()
		void BlinkToTarget();

	UFUNCTION()
		void BossSpawnFireBall();

	UFUNCTION()
		void BossSpawnBouncingFireBall();

	UFUNCTION()
		void BossSpawnSummoner();


	UFUNCTION()
	APawn* SpawnEnemy(TSubclassOf<APawn> ClassToSpawn);

	UFUNCTION()
	AActor* SpawnOrb(TSubclassOf<AActor> ClassToSpawn);

	void setCharacter(ACharacter* Character);

	UFUNCTION()
		void SetTarget(APawn* Target);


private:
	UPROPERTY(VisibleAnywhere, Category = "AIAbilities")
		TArray<class UAIBaseAbility*> GameplayAbilityArray;
		
};



//TArray - BaseAbility
//UBaseAbility* FindAbility(int Index) function


//UPROPERTY(VisibleAnywhere, Category = Gameplay)
//	class UFirstAbility* FirstAbility;

//UPROPERTY(VisibleAnywhere, Category = "Ability")
//	bool FirstAbilityFlag;

//UPROPERTY(VisibleAnywhere, Category = Gameplay)
//	class UBaseAbility* SecondAbility;

//UPROPERTY(VisibleAnywhere, Category = "Ability")
//	float firstAbilityCooldownCounter;

//UPROPERTY(VisibleAnywhere, Category = "Ability")
//	int SecondAbilityCharges;

//UPROPERTY(VisibleAnywhere, Category = "Ability")
//	float FirstAbilityCooldown;

/*UPROPERTY(EditAnywhere, Category = "AI")
	TSubclassOf<class ATrackerBot> SummonClass;

UPROPERTY(VisibleAnywhere, Category = "Ability")
	float SecondAbilityCooldownCounter;*/



	//void BlinkAbilityCooldownLogic(float time, bool abilityFlag = true);

	//void UseBlink(ACharacter* character, FVector target);

	//void Summon(ACharacter* character);

	//void SecondAbilityCooldownLogic(float time, int charges);