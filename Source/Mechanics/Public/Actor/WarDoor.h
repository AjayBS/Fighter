// Copyright ConfusedMinds Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WarDoor.generated.h"

class ACharacter;
class UInputMappingContext;

UCLASS()
class MECHANICS_API AWarDoor : public AActor
{
	GENERATED_BODY()
	
public:
	AWarDoor();

	UPROPERTY(BlueprintReadOnly)
	bool bUnlockDoor = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bShouldFlyAfterTeleport = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    UInputMappingContext* MappingContext;

	UFUNCTION(BlueprintCallable)
	void AfterTeleportOperation(ACharacter* Character);

	void AddInputMapping(ACharacter* Character);
	void RemoveInputMapping(ACharacter* Character);

	UFUNCTION()
	void DoorOperation(bool bInUnlock);

protected:
	virtual void BeginPlay() override;
};
