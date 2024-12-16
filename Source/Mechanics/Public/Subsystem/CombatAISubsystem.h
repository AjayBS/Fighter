// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "CombatAISubsystem.generated.h"

class AWarEnemy;

/**
 * 
 */
UCLASS()
class MECHANICS_API UCombatAISubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	static UCombatAISubsystem* Get(const UWorld* InWorld);
	void AddGradingAndUpdateWidget(AWarEnemy* Enemy);
	float SetScoreBasedOnDirection(AWarEnemy* Enemy);

	UFUNCTION(BlueprintCallable)
	void ResetGradingValues();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<AActor>> EnemyList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<TObjectPtr<AActor>, float> EnemyGrading;
	
};
