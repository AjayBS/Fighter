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
	FGameplayTag Montage_Attack_ComboLight1;
	FGameplayTag Montage_Attack_ComboLight2;
	FGameplayTag Montage_Attack_Heavy;

	FGameplayTag Effects_HitReact;

	TArray<FGameplayTag> DamageTypes;

	FGameplayTag Enemy_Status_Strafing;
	FGameplayTag Enemy_Status_UnderAttack;

	FGameplayTag Shared_Status_Dead;

protected:

private:
	static FWarGameplayTags GameplayTags;
 };