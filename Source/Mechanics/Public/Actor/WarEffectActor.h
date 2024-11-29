// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WarEffectActor.generated.h"

class UGameplayEffect;

UCLASS()
class MECHANICS_API AWarEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AWarEffectActor();

protected:
	virtual void BeginPlay() override;
	void ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> GameplayEffectClass);
};
