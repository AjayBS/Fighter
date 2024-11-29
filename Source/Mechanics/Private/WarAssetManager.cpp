// Fill out your copyright notice in the Description page of Project Settings.


#include "WarAssetManager.h"
#include "WarGameplayTags.h"

UWarAssetManager& UWarAssetManager::Get()
{
	check(GEngine);

	UWarAssetManager* WarAssetManager = Cast<UWarAssetManager>(GEngine->AssetManager);
	return *WarAssetManager;
}

void UWarAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FWarGameplayTags::InitializeNativeGameplayTags();
}
