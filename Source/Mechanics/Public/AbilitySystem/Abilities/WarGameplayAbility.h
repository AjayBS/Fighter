// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "WarGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class MECHANICS_API UWarGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	FGameplayTag StartupInputTag;
	
};
