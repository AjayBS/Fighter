// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * WarGameplayTags
 * Singleton containing native Gameplay Tags
 */

struct FWarGameplayTags
{
public:
	static const FWarGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();

	FGameplayTag Abilities_Primary_Punch;

	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;

	FGameplayTag Damage;
	FGameplayTag Damage_Punch;

	FGameplayTag Ability_Attack;

	FGameplayTag Montage_Attack_Weapon;
	FGameplayTag Montage_Attack_RightHand;
	FGameplayTag Montage_Attack_LeftHand;

	FGameplayTag Effects_HitReact;

	TArray<FGameplayTag> DamageTypes;

protected:

private:
	static FWarGameplayTags GameplayTags;
 };