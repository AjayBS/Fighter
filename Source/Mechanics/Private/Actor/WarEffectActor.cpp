// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/WarEffectActor.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystem/WarAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"

AWarEffectActor::AWarEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
}


void AWarEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AWarEffectActor::ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);
	if (TargetASC == nullptr)
	{
		UE_LOG(LogWarAttributeSet, Warning, TEXT("Target ASC is invalid."));
		return;
	}

	check(GameplayEffectClass);
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, 1.f, EffectContextHandle);
	TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}

