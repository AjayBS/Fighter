// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/WarAbilitySystemComponent.h"
#include "WarGameplayTags.h"

void UWarAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	for (TSubclassOf<UGameplayAbility> AbilityClass : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1.f);
		GiveAbilityAndActivateOnce(AbilitySpec);
	}

	const FWarGameplayTags& GameplayTags = FWarGameplayTags::Get();
	GEngine->AddOnScreenDebugMessage(
		-1, 
		10.f, 
		FColor::Orange, 
		FString::Printf(TEXT("Tag: %s"), *GameplayTags.Abilities_Primary_Punch.ToString()));
}
