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
	void SetActiveTile(int32 Row, int32 Column, bool bSelected);

	bool CheckIfTileIsActivelySet(int32 Row, int32 Column);

	EColorCodes GetCurrentActiveArraysColor(int32 Row, int32 Column);

	bool HandleSelectedTileOperation(bool bSelected);
	bool CheckIfAllPuzzlesAreSolved();

	UFUNCTION()
	void ClearLine(int32 Row, int32 Column, EColorCodes Color);

	void BuildPath(FTileInfo& CurrentTile, EColorCodes Color, TArray<FTileInfo>& PathTiles);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	int32 Rows;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	int32 Columns;

	int32 CurrentLinesSolved = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UGridPanel> MainGridPanel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	TSubclassOf<UUserWidget> ButtonTemplateWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	TArray<FTileInfo> InitialTileInfo;

	TArray<FTileInfo> ActiveTiles;
	TArray<FTileInfo> CurrentActiveArray;
private:	
	bool IsPathComplete(FTileInfo& Src, FTileInfo& Dest);
	bool IsAdjacent(FTileInfo& Tile1, FTileInfo& Tile2);
};
