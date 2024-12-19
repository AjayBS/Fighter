// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "WarGameplayAbility.generated.h"

class AWarCharacter;
class AWarPlayerController;

/**
 * 
 */
UCLASS()
class MECHANICS_API UWarGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
	AWarCharacter* GetPlayerCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
	AWarPlayerController* GetPlayerControllerFromActorInfo();


	UPROPERTY(EditDefaultsOnly, Category = "Input")
	FGameplayTag StartupInputTag;

private:
	TWeakObjectPtr<AWarCharacter> CachedPlayerCharacter;
	TWeakObjectPtr<AWarPlayerController> CachedPlayerController;
	
};
