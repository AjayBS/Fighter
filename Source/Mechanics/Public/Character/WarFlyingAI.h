// Copyright ConfusedMinds Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WarFlyingAI.generated.h"

UCLASS()
class MECHANICS_API AWarFlyingAI : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> PerceptionPoint;

	AWarFlyingAI();

};
