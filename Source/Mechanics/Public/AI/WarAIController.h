// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "WarAIController.generated.h"

class UBlackboardComponent;
class UBehaviorTreeComponent;

/**
 * 
 */
UCLASS()
class MECHANICS_API AWarAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AWarAIController();

protected:
	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehavioreTreeComponent;

};
