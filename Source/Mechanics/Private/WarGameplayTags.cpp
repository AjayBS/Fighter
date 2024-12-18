// Fill out your copyright notice in the Description page of Project Settings.


#include "WarGameplayTags.h"
#include "GameplayTagsManager.h"

FWarGameplayTags FWarGameplayTags::GameplayTags;

void FWarGameplayTags::InitializeNativeGameplayTags()
{
	GameplayTags.Abilities_Primary_Punch = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Primary.Punch"), 
		FString("Punching a character")
		);

	/**
	 * Input Tags
	 */

	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.LMB"),
		FString("Input tag for Left Mouse Button.")
	);

	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.RMB"),
		FString("Input tag for Right Mouse Button.")
	);

	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.1"),
		FString("Input tag for 1 key.")
	);

	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage"),
		FString("Damage.")
	);

	GameplayTags.Ability_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Attack"),
		FString("Attack ability tag.")
	);

	GameplayTags.Damage_Punch = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Punch"),
		FString("Add physical punch damage.")
	);

	/**
	 * Hit react
	 */

	GameplayTags.Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effects.HitReact"),
		FString("Hit react effects.")
	);

	/**
	 * Montage
	 */

	GameplayTags.Damage_Punch = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.Weapon"),
		FString("Weapon.")
		);

	GameplayTags.Montage_Attack_RightHand = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.RightHand"),
		FString("Right Hand.")
	);

	GameplayTags.Montage_Attack_LeftHand = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.LeftHand"),
		FString("LeftHand.")
	);

	/**
	 * Enemy tags
	 */

	GameplayTags.Enemy_Status_Strafing = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Enemy.Status.Strafing"),
		FString("Enemy Strafing.")
	);

	GameplayTags.Enemy_Status_UnderAttack = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Enemy.Status.UnderAttack"),
		FString("Enemy is under attack.")
	);

	GameplayTags.Shared_Status_Dead = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Shared.Status.Dead"),
		FString("Dead.")
	);
}
