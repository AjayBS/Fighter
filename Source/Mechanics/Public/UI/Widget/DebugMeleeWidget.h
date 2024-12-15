// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/WarUserWidget.h"
#include "DebugMeleeWidget.generated.h"

/**
 * 
 */
UCLASS()
class MECHANICS_API UDebugMeleeWidget : public UWarUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Debug")
	TObjectPtr<AActor> EnemyInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	float FightingGrade;
	
};
