// Copyright ConfusedMinds Inc.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTS_DistanceToTarget.generated.h"

/**
 * 
 */
UCLASS()
class MECHANICS_API UBTS_DistanceToTarget : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTS_DistanceToTarget();

	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	virtual FString GetStaticDescription() const override;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = "Target")
	FBlackboardKeySelector InIsCloseEnough;

	UPROPERTY(EditAnywhere, Category = "Target")
	float DistanceThreshold;
};
