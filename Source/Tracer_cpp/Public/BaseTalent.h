// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseTalent.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class TRACER_CPP_API UBaseTalent : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Talent")
	FText Name;

	UPROPERTY(EditAnywhere, Category = "Talent")
	int rank;

	UPROPERTY(EditAnywhere, Category = "Talent")
	int maxRank;
	
	UPROPERTY(EditAnywhere, Category = "Talent")
	int pointsToUnlock;

	UPROPERTY(EditAnywhere, Category = "Talent")
	int pointSpent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Talent")
	bool bLock;


public:

	UFUNCTION(BlueprintCallable, Category = "Talent")
	virtual void RankUp();

	UFUNCTION(BlueprintCallable, Category = "Talent")
	virtual void Unlock();

	UFUNCTION(BlueprintCallable, Category = "Talent")
	virtual void Lock();

	UFUNCTION()
	int GetActualRank();

	UFUNCTION()
	int GetMaxRank();

	UFUNCTION()
	int GetPointsToUnlock();

	UFUNCTION()
	FORCEINLINE bool GetbLock() { return bLock;	}


};
