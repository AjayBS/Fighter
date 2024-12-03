// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/WarCharacterBase.h"
#include "Interfaces/EnemyInterface.h"
#include "Character/CharacterClassInfo.h"
#include "WarEnemy.generated.h"

/**
 * 
 */
UCLASS()
class MECHANICS_API AWarEnemy : public AWarCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

protected:
	virtual void InitialzeDefaultAttributes() const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	ECharacterClass CharacterClass = ECharacterClass::Elementalist;

	virtual void BeginPlay() override;
};
