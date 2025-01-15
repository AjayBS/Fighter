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

	GameplayTags.Abilities_Primary_Punch = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Primary.Stone"),
		FString("Throws a stone to distract a character.")
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

	GameplayTags.InputTag_MustBeHeld = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.MustBeHeld"),
		FString("Input tag for holding.")
	);

	GameplayTags.InputTag_MustBeHeld_Block = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.MustBeHeld.Block"),
		FString("Input tag held which blocks an attack.")
	);

	GameplayTags.InputTag_Target = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.Target"),
		FString("Input for targeting a character.")
	);

	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage"),
		FString("Damage.")
	);

	GameplayTags.Ability_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Attack"),
		FString("Attack ability tag.")
	);

	GameplayTags.Ability_Block = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Block"),
		FString("Block ability tag.")
	);

	GameplayTags.Ability_Status_Block = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Status.Block"),
		FString("Block status.")
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

	GameplayTags.Player_Effects_HitPause = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effects.HitPause"),
		FString("Hit pause effects.")
	); 

	/**
	 * Montage
	 */

	GameplayTags.Damage_Punch = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.Weapon"),
		FString("Weapon.")
		);

	GameplayTags.Montage_Attack_ComboLight1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.ComboLight1"),
		FString("Right Hand Light Punch.")
	);

	GameplayTags.Montage_Attack_ComboLight2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.ComboLight2"),
		FString("Combo of Right Leg Light kick.")
	);

	GameplayTags.Montage_Attack_Heavy = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.Heavy"),
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
	
	GameplayTags.Player_Event_SuccessfulBlock = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Player.Event.SuccessfulBlock"),
			FString("Event for a successful block.")
	);
}
