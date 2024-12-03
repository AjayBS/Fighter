// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MechanicsGameMode.generated.h"

class UCharacterClassInfo;

UCLASS(minimalapi)
class AMechanicsGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMechanicsGameMode();

	UPROPERTY(EditDefaultsOnly, Category = "Character Class Defaults")
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;
};



