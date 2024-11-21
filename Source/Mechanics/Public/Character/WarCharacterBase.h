// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WarCharacterBase.generated.h"

UCLASS(Abstract)
class MECHANICS_API AWarCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AWarCharacterBase();

protected:
	virtual void BeginPlay() override;
};
