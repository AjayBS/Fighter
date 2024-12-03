// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/Abilities/WarBasicAttack.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "WarGameplayTags.h"

void UWarBasicAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, 
						const FGameplayAbilityActorInfo* ActorInfo, 
						const FGameplayAbilityActivationInfo ActivationInfo, 
						const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwningActorFromActorInfo());
	FGameplayEffectContextHandle EffectContextHandle = SourceASC->MakeEffectContext();
	UKismetSystemLibrary::PrintString(this, FString("ActivateAbility (C++)"), true, true, FLinearColor::Yellow, 3);
	const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), EffectContextHandle);

	const FWarGameplayTags GameplayTags = FWarGameplayTags::Get();

	for (auto& Pair : DamageTypes)
	{
		const float ScaledDamage = Pair.Value.GetValueAtLevel(GetAbilityLevel());
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, Pair.Key, ScaledDamage);
	}
}
