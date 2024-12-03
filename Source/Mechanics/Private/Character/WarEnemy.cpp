// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WarEnemy.h"
#include "WarBlueprintSystemLibrary.h"

void AWarEnemy::InitialzeDefaultAttributes() const
{
	UWarBlueprintSystemLibrary::InitializeDefaultAttributes(this, AbilitySystemComponent, CharacterClass, Level);
}

void AWarEnemy::BeginPlay()
{
	Super::BeginPlay();
}
