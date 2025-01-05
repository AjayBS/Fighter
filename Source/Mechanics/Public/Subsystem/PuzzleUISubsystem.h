// Copyright ConfusedMinds Inc.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "PuzzleUISubsystem.generated.h"

class UWarUserWidget;

/**
 * 
 */
UCLASS()
class MECHANICS_API UPuzzleUISubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void OpenPuzzleWidget(TSubclassOf<UWarUserWidget> UserWidgetClass);
	
};
