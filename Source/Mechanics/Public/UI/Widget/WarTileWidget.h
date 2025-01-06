// Copyright ConfusedMinds Inc.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Subsystem/PuzzleUISubsystem.h"
#include "WarTileWidget.generated.h"

/**
 * 
 */
UCLASS()
class MECHANICS_API UWarTileWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void BP_UpdateColorValue(EColorCodes Color);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	int32 RowIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	int32 ColumnIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	EColorCodes ColorCode = EColorCodes::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	bool IsAssigned;
};
