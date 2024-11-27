// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/WarCharacterBase.h"
#include "Interfaces/EnemyInterface.h"
#include "WarEnemy.generated.h"

/**
 * 
 */
UCLASS()
class MECHANICS_API AWarEnemy : public AWarCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()	
};
