// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WarCharacterBase.h"

AWarCharacterBase::AWarCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

UAbilitySystemComponent* AWarCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AWarCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

