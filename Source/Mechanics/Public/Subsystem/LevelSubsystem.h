// Copyright ConfusedMinds Inc.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "LevelSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDoorOperation, bool, bUnlockDoor);

/**
 * 
 */
UCLASS()
class MECHANICS_API ULevelSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	static ULevelSubsystem* Get(const UWorld* InWorld);
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

	UFUNCTION(BlueprintCallable)
	void EnemyDefeated();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FDoorOperation DoorOperation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NumberOfEnemies;

	int32 CurrentEnemyDefeatCount;
	
};
