// Fill out your copyright notice in the Description page of Project Settings.


#include "WarBlueprintSystemLibrary.h"
#include "Player/WarPlayerController.h"
#include "Mechanics/MechanicsGameMode.h"
#include "AbilitySystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Interfaces/CombatInterface.h"
#include "Character/CharacterClassInfo.h"
#include "GameplayEffectTypes.h"
#include "Engine/OverlapResult.h"

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

void UWarBlueprintSystemLibrary::GetLivePlayersWithinRadius(const UObject* WorldContextObject, TArray<AActor*>& OutOverlappingActors, 
	const TArray<AActor*>& ActorsToIgnore, 
	float Radius, const FVector& SphereOrigin)
{
	FCollisionQueryParams SphereParams;
	SphereParams.AddIgnoredActors(ActorsToIgnore);

	TArray<FOverlapResult> Overlaps;
	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		World->OverlapMultiByObjectType(Overlaps, SphereOrigin, FQuat::Identity, 
			FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllDynamicObjects), 
			FCollisionShape::MakeSphere(Radius), SphereParams);

		for (FOverlapResult& Overlap : Overlaps)
		{
			const bool ImplementsCombatInterface = Overlap.GetActor()->Implements<UCombatInterface>();

			// TO-DO Check for is dead.

			if (ImplementsCombatInterface)
			{
				OutOverlappingActors.AddUnique(ICombatInterface::Execute_GetAvatar(Overlap.GetActor()));
			}
		}
	}
}
