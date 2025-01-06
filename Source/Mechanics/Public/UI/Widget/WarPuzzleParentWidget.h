// Copyright ConfusedMinds Inc.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/WarUserWidget.h"
#include "Subsystem/PuzzleUISubsystem.h"
#include "WarPuzzleParentWidget.generated.h"

class UGridPanel;

/**
 * 
 */
UCLASS()
class MECHANICS_API UWarPuzzleParentWidget : public UWarUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;

	UFUNCTION(BlueprintCallable)
	void CreateGrid();

	UFUNCTION(BlueprintCallable)
	void SetActiveTile(int32 Row, int32 Column);

	bool CheckIfTileIsActivelySet(int32 Row, int32 Column);

	EColorCodes GetCurrentActiveArraysColor(int32 Row, int32 Column);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	int32 Rows;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	int32 Columns;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UGridPanel> MainGridPanel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	TSubclassOf<UUserWidget> ButtonTemplateWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	TArray<FTileInfo> InitialTileInfo;

	TArray<FTileInfo> ActiveTiles;
	TArray<FTileInfo> CurrentActiveArray;
};
