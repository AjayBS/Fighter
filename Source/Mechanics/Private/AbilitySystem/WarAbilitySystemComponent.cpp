// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/WarAbilitySystemComponent.h"
#include "WarGameplayTags.h"
#include "AbilitySystem/Abilities/WarGameplayAbility.h"

DEFINE_LOG_CATEGORY_STATIC(LogWarAbilitySystemComponent, Warning, All);

void UWarAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	for (const TSubclassOf<UGameplayAbility> AbilityClass : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1.f);
		if (const UWarGameplayAbility* WarAbility = Cast<UWarGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(WarAbility->StartupInputTag);
			GiveAbility(AbilitySpec);
		}
	}
}

void UWarAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid())
	{
		UE_LOG(LogWarAbilitySystemComponent, Warning, TEXT("InputTag is invalid for character %s"), *GetOwnerActor()->GetName());
		return;
	}

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			if (!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}	
}

void UWarAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid())
	{
		UE_LOG(LogWarAbilitySystemComponent, Warning, TEXT("InputTag is invalid for character %s"), *GetOwnerActor()->GetName());
		return;
	}

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(AbilitySpec);
		}
	}
}
