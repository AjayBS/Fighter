// Copyright ConfusedMinds Inc.

#include "Subsystem/LevelSubsystem.h"

ULevelSubsystem* ULevelSubsystem::Get(const UWorld* InWorld)
{
	if (InWorld)
	{
		return InWorld->GetSubsystem<ULevelSubsystem>();
	}

	return nullptr;
}

void ULevelSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	DoorOperation.Broadcast(false);
	CurrentEnemyDefeatCount = 0;
}

void ULevelSubsystem::EnemyDefeated()
{
	CurrentEnemyDefeatCount++;

	if (CurrentEnemyDefeatCount >= NumberOfEnemies)
	{
		DoorOperation.Broadcast(true);
	}
}
