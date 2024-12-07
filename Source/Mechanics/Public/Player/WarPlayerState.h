// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "WarPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class MECHANICS_API AWarPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	AWarPlayerState();
	FORCEINLINE int32 GetPlayerLevel() const { return Level; }
	
private:
	UPROPERTY(VisibleAnywhere)
	int32 Level = 1;
};
