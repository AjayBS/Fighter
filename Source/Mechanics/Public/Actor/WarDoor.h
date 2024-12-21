// Copyright ConfusedMinds Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WarDoor.generated.h"

UCLASS()
class MECHANICS_API AWarDoor : public AActor
{
	GENERATED_BODY()
	
public:
	AWarDoor();

	UPROPERTY(BlueprintReadOnly)
	bool bUnlockDoor = false;

	UFUNCTION()
	void DoorOperation(bool bInUnlock);

protected:
	virtual void BeginPlay() override;
};
