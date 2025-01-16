// Copyright ConfusedMinds Inc.


#include "UI/Widget/WarPuzzleParentWidget.h"

#include "Components/GridPanel.h"
#include "UI/Widget/WarTileWidget.h"
#include "Subsystem/PuzzleUISubsystem.h"

void UWarPuzzleParentWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	CreateGrid();

	TArray<UWidget*> Widgets = MainGridPanel->GetAllChildren();
	for (int32 i = 0; i < Widgets.Num(); i++)
	{
		UWarTileWidget* WarTile = Cast<UWarTileWidget>(Widgets[i]);
		WarTileWidgets.Add(WarTile);
	}

	if (UPuzzleUISubsystem* PuzzleSubsystem = UPuzzleUISubsystem::Get(GetWorld()))
	{
		PuzzleSubsystem->TileActivated.AddDynamic(this, &UWarPuzzleParentWidget::SetActiveTile);
		PuzzleSubsystem->ClearLine.AddDynamic(this, &UWarPuzzleParentWidget::ClearLine);
	}
}

void UWarPuzzleParentWidget::CreateGrid()
{
	if (ButtonTemplateWidget.Get() == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Please instantiate a button widget."));
		return;
	}

	for (int32 i = 0; i < Rows; i++)
	{
		for (int32 j = 0; j < Columns; j++)
		{
			if (MainGridPanel != nullptr)
			{
				UWarTileWidget* ButtonWidget = CreateWidget<UWarTileWidget>(GetWorld(), ButtonTemplateWidget);

				if (ButtonWidget == nullptr)
				{
					UE_LOG(LogTemp, Error, TEXT("Widget cannot be created. Please instantiate from WarTileWidget."));
					continue;
				}

				ButtonWidget->RowIndex = i;
				ButtonWidget->ColumnIndex = j;

				for (const auto& Info : InitialTileInfo)
				{
					if (ButtonWidget->RowIndex == Info.Row && ButtonWidget->ColumnIndex == Info.Column)
					{
						ButtonWidget->ColorCode = Info.Color;
						ButtonWidget->IsAssigned = true;
					}
				}

				MainGridPanel->AddChildToGrid(ButtonWidget, i, j);
			}			
		}
	}
}

void UWarPuzzleParentWidget::SetActiveTile(int32 Row, int32 Column, bool bSelected)
{
	if (HandleSelectedTileOperation(bSelected, Row, Column))
	{		
		if (CheckIfAllPuzzlesAreSolved())
		{
			// Puzzle solved here. Do operations after puzzle is solved.
			if (UPuzzleUISubsystem* PuzzleSubsystem = UPuzzleUISubsystem::Get(GetWorld()))
			{
				PuzzleSubsystem->PuzzleCompleted.Broadcast(this);
			}
			RemoveFromParent();
		}
		return;
	}

	if (!CheckIfTileIsActivelySet(Row, Column))
	{
		// Visually set the active tile.
		for (int32 i = 0; i < WarTileWidgets.Num(); i++)
		{
			UWarTileWidget* WarTile = WarTileWidgets[i];
			if (WarTile->RowIndex == Row && WarTile->ColumnIndex == Column)
			{
				// Search for current active array and assign
				EColorCodes Color = GetCurrentActiveArraysColor(Row, Column);
				UE_LOG(LogTemp, Verbose, TEXT("Color of the widget is %d."), Color);
				if (Color != EColorCodes::None || WarTile->ColorCode != EColorCodes::None)
				{
					if (!WarTile->IsAssigned)
					{
						WarTile->BP_UpdateColorValue(Color);
						CurrentActiveArray.Add(FTileInfo(Color, WarTile->RowIndex, WarTile->ColumnIndex));
					}
					else
					{
						CurrentActiveArray.Empty();
						CurrentActiveArray.Add(FTileInfo(WarTile->ColorCode, WarTile->RowIndex, WarTile->ColumnIndex));
					}

					ActiveTiles.Add(FTileInfo(WarTile->ColorCode, Row, Column));
				}
				break;
			}			
		}
	}
}

bool UWarPuzzleParentWidget::CheckIfTileIsActivelySet(int32 Row, int32 Column)
{
	for (int32 i = 0; i < ActiveTiles.Num(); i++)
	{
		if (ActiveTiles[i].Row == Row && ActiveTiles[i].Column == Column)
		{
			UE_LOG(LogTemp, Verbose, TEXT("Passing an active tile. No action is taken"));
			return true;
		}
	}

	return false;
}

EColorCodes UWarPuzzleParentWidget::GetCurrentActiveArraysColor(int32 Row, int32 Column)
{
	if (CurrentActiveArray.Num() > 0)
	{
		FTileInfo LatestAddedArray = CurrentActiveArray[CurrentActiveArray.Num() - 1];
		if ((LatestAddedArray.Row == Row - 1 && LatestAddedArray.Column == Column) ||
			(LatestAddedArray.Row == Row + 1 && LatestAddedArray.Column == Column) ||
			(LatestAddedArray.Row == Row && LatestAddedArray.Column == Column - 1) ||
			(LatestAddedArray.Row == Row && LatestAddedArray.Column == Column + 1)
			)
		{
			return LatestAddedArray.Color;
		}
	}

	return EColorCodes::None;
}

bool UWarPuzzleParentWidget::HandleSelectedTileOperation(bool bSelected, int32 Row, int32 Column)
{
	if (bSelected)
	{
		if (CurrentActiveArray.IsEmpty())
		{
			return false;
		}
		else
		{
			// Do a DFS search here to make sure all lines are connected.
			FTileInfo SrcTile, DestTile;
			for (int32 i = 0; i < InitialTileInfo.Num(); i++)
			{
				if (CurrentActiveArray[0].Color == InitialTileInfo[i].Color)
				{
					if (SrcTile.Color == EColorCodes::None)
					{
						SrcTile = InitialTileInfo[i];
					}
					else
					{
						DestTile = InitialTileInfo[i];
					}
				}
			}

			if (IsPathComplete(SrcTile, DestTile, Row, Column))
			{
				CurrentLinesSolved++;
				UE_LOG(LogTemp, Warning, TEXT("Puzzle solved here. Number of lines increased to %d"), CurrentLinesSolved);
				SolvedTileArray.Add(CurrentActiveArray);
				CurrentActiveArray.Empty();
				return true;
			}
			else
			{
				ClearLine(SrcTile.Row, SrcTile.Column, SrcTile.Color);
				return true;
			}
		}
	}

	return false;
}

bool UWarPuzzleParentWidget::CheckIfAllPuzzlesAreSolved()
{
	return CurrentLinesSolved == (InitialTileInfo.Num() / 2);
}

void UWarPuzzleParentWidget::ClearLine(int32 Row, int32 Column, EColorCodes Color)
{
	if (Color != EColorCodes::None)
	{
		TArray<FTileInfo> PathTiles;
		EColorCodes TargetColor = Color;

		for (int32 i = 0; i < InitialTileInfo.Num(); i++)
		{
			if (Color == InitialTileInfo[i].Color)
			{
				FTileInfo TileInfo = InitialTileInfo[i];
				BuildPath(TileInfo, Color, PathTiles);
			}			
		}

		for (FTileInfo& TileInPath : PathTiles)
		{
			UWarTileWidget* Widget = GetWidgetAtTile(TileInPath.Row, TileInPath.Column);
			if (!Widget->IsAssigned)
			{
				Widget->BP_UpdateColorValue(EColorCodes::None);
			}

			RemoveElementFromActiveTiles(TileInPath);
		}

		// Clear empty active array
		if (CurrentActiveArray.Num() > 0)
		{
			if (CurrentActiveArray[0].Color == Color)
			{
				CurrentActiveArray.Empty();
			}
		}
		else
		{
			RemoveElementFromSolvedTileArray(Color);
		}
	}
}

void UWarPuzzleParentWidget::BuildPath(FTileInfo& CurrentTile, EColorCodes Color, TArray<FTileInfo>& PathTiles)
{
	if (PathTiles.Contains(CurrentTile)) return;

	if (CurrentTile.Color != Color) return;

	PathTiles.Add(CurrentTile);

	TArray<FTileInfo> Neighbors = GetAdjacentTiles(CurrentTile);

	for (FTileInfo& Neighbor : Neighbors)
	{
		BuildPath(Neighbor, Color, PathTiles);
	}
}

TArray<FTileInfo> UWarPuzzleParentWidget::GetAdjacentTiles(FTileInfo& CurrentTile)
{
	TArray<FTileInfo> AdjacentTiles;

	if (CurrentTile.Color == EColorCodes::None) return AdjacentTiles;

	int32 Row = CurrentTile.Row;
	int32 Col = CurrentTile.Column;

	TArray<FIntPoint> Offsets = {
		FIntPoint(-1, 0),
		FIntPoint(1, 0),
		FIntPoint(0, -1),
		FIntPoint(0, 1)
	};

	for (const FIntPoint& Offset : Offsets)
	{
		int32 NeighborRow = Row + Offset.X;
		int32 NeighborCol = Col + Offset.Y;
		if (IsValidTile(NeighborRow, NeighborCol)) {
			FTileInfo NeighborTile = GetTileAt(NeighborRow, NeighborCol);
			AdjacentTiles.Add(NeighborTile);
		}
	}

	return AdjacentTiles;
}

bool UWarPuzzleParentWidget::IsValidTile(int32 Row, int32 Col) const
{
	return Row >= 0 && Row < Rows && Col >= 0 && Col < Columns;
}

FTileInfo UWarPuzzleParentWidget::GetTileAt(int32 Row, int32 Col) const
{
	for (int32 i = 0; i < WarTileWidgets.Num(); i++)
	{
		if (Row == WarTileWidgets[i]->RowIndex && Col == WarTileWidgets[i]->ColumnIndex)
		{
			return FTileInfo(WarTileWidgets[i]->ColorCode, Row, Col);
		}
	}
	return FTileInfo();
}

UWarTileWidget* UWarPuzzleParentWidget::GetWidgetAtTile(int32 Row, int32 Col) const
{
	for (int32 i = 0; i < WarTileWidgets.Num(); i++)
	{
		if (Row == WarTileWidgets[i]->RowIndex && Col == WarTileWidgets[i]->ColumnIndex)
		{
			return WarTileWidgets[i];
		}
	}

	return nullptr;
}

bool UWarPuzzleParentWidget::IsPathComplete(FTileInfo& Src, FTileInfo& Dest, int32 CurrentRowClicked, int32 CurrentColumnClicked)
{
	if (CurrentActiveArray.Num() < 2)
	{
		return false;
	}

	for (int32 i = 0; i < CurrentActiveArray.Num() - 1; ++i)
	{
		FTileInfo Tile1 = CurrentActiveArray[i];
		FTileInfo Tile2 = CurrentActiveArray[i + 1];

		if (!IsAdjacent(Tile1, Tile2))
		{
			return false;
		}
	}

	if (CurrentColumnClicked == Src.Column && CurrentRowClicked == Src.Row)
	{
		return IsAdjacent(CurrentActiveArray.Last(), Src);
	}
	else
	{
		return IsAdjacent(CurrentActiveArray.Last(), Dest);
	}
}

bool UWarPuzzleParentWidget::IsAdjacent(FTileInfo& Tile1, FTileInfo& Tile2)
{
	int32 RowDiff = FMath::Abs(Tile1.Row - Tile2.Row);
	int32 ColDiff = FMath::Abs(Tile1.Column - Tile2.Column);
	return RowDiff + ColDiff == 1;
}

void UWarPuzzleParentWidget::RemoveElementFromActiveTiles(FTileInfo& InTile)
{
	for (int32 i = ActiveTiles.Num() - 1; i >= 0; --i)
	{
		if (InTile.Row == ActiveTiles[i].Row
			&& InTile.Column == ActiveTiles[i].Column
			&& InTile.Color == ActiveTiles[i].Color)
		{
			ActiveTiles.RemoveAt(i);
		}
	}
}

void UWarPuzzleParentWidget::RemoveElementFromSolvedTileArray(EColorCodes Color)
{
	for (int32 i = SolvedTileArray.Num() - 1; i >= 0; --i)
	{
		for (int32 j = SolvedTileArray[i].Num() - 1; j >= 0; --j)
		{
			if (Color == SolvedTileArray[i][j].Color)
			{
				SolvedTileArray.RemoveAt(i);
				CurrentLinesSolved--;
				UE_LOG(LogTemp, Warning, TEXT("Puzzle solved here. Number of lines decreased to %d"), CurrentLinesSolved);
				break;
			}
		}
	}
}
