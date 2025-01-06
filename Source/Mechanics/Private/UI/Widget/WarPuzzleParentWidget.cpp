// Copyright ConfusedMinds Inc.


#include "UI/Widget/WarPuzzleParentWidget.h"

#include "Components/GridPanel.h"
#include "UI/Widget/WarTileWidget.h"
#include "Subsystem/PuzzleUISubsystem.h"

void UWarPuzzleParentWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	CreateGrid();

	if (UPuzzleUISubsystem* PuzzleSubsystem = UPuzzleUISubsystem::Get(GetWorld()))
	{
		PuzzleSubsystem->TileActivated.AddDynamic(this, &UWarPuzzleParentWidget::SetActiveTile);
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
	if (HandleSelectedTileOperation(bSelected))
	{
		return;
	}

	if (!CheckIfTileIsActivelySet(Row, Column))
	{
		// Visually set the active tile.
		TArray<UWidget*> Widgets = MainGridPanel->GetAllChildren();
		for (int32 i = 0; i < Widgets.Num(); i++)
		{
			UWarTileWidget* WarTile = Cast<UWarTileWidget>(Widgets[i]);
			if (WarTile->RowIndex == Row && WarTile->ColumnIndex == Column)
			{
				// Search for current active array and assign
				EColorCodes Color = GetCurrentActiveArraysColor(Row, Column);
				UE_LOG(LogTemp, Error, TEXT("Color of the widget is %d."), Color);
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
			UE_LOG(LogTemp, Error, TEXT("Passing an active tile. No action is taken"));
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

bool UWarPuzzleParentWidget::HandleSelectedTileOperation(bool bSelected)
{
	if (bSelected)
	{
		if (CurrentActiveArray.IsEmpty())
		{
			return false;
		}
		else
		{
			CurrentActiveArray.Empty();
			return true;
		}
	}

	return false;
}
