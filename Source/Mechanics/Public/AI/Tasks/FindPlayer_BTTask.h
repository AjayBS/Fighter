// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "FindPlayer_BTTask.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class MECHANICS_API UFindPlayer_BTTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UFindPlayer_BTTask();

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector PlayerKey;
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search", meta = (AllowProtectedAccess = "true"))
	bool SearchRandom = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search", meta = (AllowProtectedAccess = "true"))
	float SearchRadius = false;
};
