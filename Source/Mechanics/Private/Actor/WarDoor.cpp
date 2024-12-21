// Copyright ConfusedMinds Inc.


#include "Actor/WarDoor.h"
#include "Subsystem/LevelSubsystem.h"

AWarDoor::AWarDoor()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AWarDoor::DoorOperation(bool bInUnlock)
{
	bUnlockDoor = bInUnlock;
}

void AWarDoor::BeginPlay()
{
	Super::BeginPlay();
	
	if (ULevelSubsystem* LevelSubsystem = ULevelSubsystem::Get(GetWorld()))
	{
		LevelSubsystem->DoorOperation.AddDynamic(this, &AWarDoor::DoorOperation);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get a level subsytem in %s"), *GetName());
	}
}

