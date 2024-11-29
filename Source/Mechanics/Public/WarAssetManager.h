// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "WarAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class MECHANICS_API UWarAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	static UWarAssetManager& Get();

protected:
	virtual void StartInitialLoading();
	
};
