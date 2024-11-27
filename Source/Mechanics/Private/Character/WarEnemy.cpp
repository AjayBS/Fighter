// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WarEnemy.h"

#include "AbilitySystem/WarAbilitySystemComponent.h"
#include "AbilitySystem/WarAttributeSet.h"

AWarEnemy::AWarEnemy()
{
	AbilitySystemComponent = CreateDefaultSubobject<UWarAbilitySystemComponent>("AbilitySystemComponent");
	AttributeSet = CreateDefaultSubobject<UWarAttributeSet>("AttributeSet");
}
