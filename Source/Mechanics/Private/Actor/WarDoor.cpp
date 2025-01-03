// Copyright ConfusedMinds Inc.


#include "Actor/WarDoor.h"
#include "Subsystem/LevelSubsystem.h"
#include "EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputMappingContext.h"

AWarDoor::AWarDoor()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AWarDoor::AfterTeleportOperation(ACharacter* Character)
{
	if (Character == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Please pass in a character to do after teleport operations."));
		return;
	}

	if (bShouldFlyAfterTeleport)
	{
		Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
		Character->GetCharacterMovement()->bOrientRotationToMovement = false;
		AddInputMapping(Character);
	}
	else
	{
		Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		Character->GetCharacterMovement()->bOrientRotationToMovement = true;
		RemoveInputMapping(Character);
	}
}

void AWarDoor::AddInputMapping(ACharacter* Character)
{
	if (Character == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get a valid character."));
	}

	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			if (MappingContext)
			{
				Subsystem->AddMappingContext(MappingContext, 1); // Priority 1
			}
		}
	}
}

void AWarDoor::RemoveInputMapping(ACharacter* Character)
{
	if (Character == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get a valid character."));
	}

	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			if (MappingContext)
			{
				Subsystem->RemoveMappingContext(MappingContext);
			}
		}
	}
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

