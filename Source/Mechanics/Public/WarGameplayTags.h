// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * WarGameplayTags
 * Singleton containing native Gameplay Tags
 */

struct FWarGameplayTags
{
public:
	static const FWarGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();
protected:

private:
static FWarGameplayTags GameplayTags;
 };