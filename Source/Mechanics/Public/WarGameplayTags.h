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
	FGameplayTag Abilities_Throw_Stone;

	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_Target;

	FGameplayTag InputTag_MustBeHeld;
	FGameplayTag InputTag_MustBeHeld_Block;

	FGameplayTag Damage;
	FGameplayTag Damage_Punch;

	FGameplayTag Ability_Attack;
	FGameplayTag Ability_Block;

	FGameplayTag Ability_Status_Block;

	FGameplayTag Montage_Attack_Weapon;
	FGameplayTag Montage_Attack_ComboLight1;
	FGameplayTag Montage_Attack_ComboLight2;
	FGameplayTag Montage_Attack_Heavy;

	FGameplayTag Effects_HitReact;
	FGameplayTag Player_Effects_HitPause;

	TArray<FGameplayTag> DamageTypes;

	FGameplayTag Enemy_Status_Strafing;
	FGameplayTag Enemy_Status_UnderAttack;

	FGameplayTag Shared_Status_Dead;

	FGameplayTag Player_Event_SuccessfulBlock;

protected:

private:
	static FWarGameplayTags GameplayTags;
 };