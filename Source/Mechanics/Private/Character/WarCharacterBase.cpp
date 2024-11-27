// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WarCharacterBase.h"

#include "AbilitySystem/WarAbilitySystemComponent.h"
#include "AbilitySystem/WarAttributeSet.h"

AWarCharacterBase::AWarCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	AbilitySystemComponent = CreateDefaultSubobject<UWarAbilitySystemComponent>("AbilitySystemComponent");
	AttributeSet = CreateDefaultSubobject<UWarAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* AWarCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AWarCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

