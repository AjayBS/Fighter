// Copyright ConfusedMinds Inc.


#include "UI/Widget/WarPuzzleParentWidget.h"

#include "Components/GridPanel.h"

void UWarPuzzleParentWidget::CreateGrid(int32 RowLength, int32 ColumnLength)
{
	if (ButtonTemplateWidget.Get() == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Please instantiate a button widget."));
		return;
	}

	for (int32 i = 0; i < RowLength; i++)
	{
		for (int32 j = 0; j < ColumnLength; j++)
		{
			if (MainGridPanel != nullptr)
			{
				UUserWidget* ButtonWidget = CreateWidget<UUserWidget>(GetWorld(), ButtonTemplateWidget);
				MainGridPanel->AddChildToGrid(ButtonWidget, i, j);
			}			
		}
	}
}
