// Fill out your copyright notice in the Description page of Project Settings.


#include "WarGameplayTags.h"
#include "GameplayTagsManager.h"

FWarGameplayTags FWarGameplayTags::GameplayTags;

void FWarGameplayTags::InitializeNativeGameplayTags()
{
	UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Primary.Punch"), FString("Punching a character"));
}
