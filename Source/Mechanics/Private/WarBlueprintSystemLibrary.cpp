// Fill out your copyright notice in the Description page of Project Settings.


#include "WarBlueprintSystemLibrary.h"
#include "Player/WarPlayerController.h"
#include "Mechanics/MechanicsGameMode.h"
#include "AbilitySystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Interfaces/CombatInterface.h"
#include "Character/CharacterClassInfo.h"
#include "GameplayEffectTypes.h"

DEFINE_LOG_CATEGORY_STATIC(LogWarBlueprintLibrary, Warning, All);

void UWarBlueprintSystemLibrary::GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, ECharacterClass CharacterClass)
{
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	if (CharacterClassInfo == nullptr) return;
	for (TSubclassOf<UGameplayAbility> AbilityClass : CharacterClassInfo->CommonAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		ASC->GiveAbility(AbilitySpec);
	}
	const FCharacterClassDefaultInfo& DefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
	for (TSubclassOf<UGameplayAbility> AbilityClass : DefaultInfo.StartupAbilities)
	{
		if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(ASC->GetAvatarActor()))
		{
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, CombatInterface->GetPlayerLevel());
			ASC->GiveAbility(AbilitySpec);
		}
	}
}

UCharacterClassInfo* UWarBlueprintSystemLibrary::GetCharacterClassInfo(const UObject* WorldContextObject)
{
	AMechanicsGameMode* WarGameMode = Cast<AMechanicsGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (WarGameMode == nullptr) 
	{
		return nullptr;
	}
	return WarGameMode->CharacterClassInfo;
}

void UWarBlueprintSystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, ECharacterClass CharacterClass, float Level)
{
	AMechanicsGameMode* WarGameMode = Cast<AMechanicsGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (WarGameMode == nullptr)
	{
		UE_LOG(LogWarBlueprintLibrary, Warning, TEXT("Game mode is nullptr. Returning."));
		return;
	}

	FCharacterClassDefaultInfo ClassDefaultInfo = WarGameMode->CharacterClassInfo->GetClassDefaultInfo(CharacterClass);	
	
	const FGameplayEffectSpecHandle PrimaryAttributesSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttributes, Level, ASC->MakeEffectContext());
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data.Get());

	const FGameplayEffectSpecHandle SecondaryAttributesSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.SecondaryAttributes, Level, ASC->MakeEffectContext());
	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributesSpecHandle.Data.Get());

	for (TSubclassOf<UGameplayAbility> AbilityClass : ClassDefaultInfo.StartupAbilities)
	{
	}
}
