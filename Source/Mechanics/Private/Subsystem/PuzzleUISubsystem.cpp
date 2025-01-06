// Copyright ConfusedMinds Inc.

#include "Subsystem/PuzzleUISubsystem.h"

#include "UI/Widget/WarUserWidget.h"

UPuzzleUISubsystem* UPuzzleUISubsystem::Get(const UWorld* InWorld)
{
	if (InWorld)
	{
		return InWorld->GetSubsystem<UPuzzleUISubsystem>();
	}

	return nullptr;
}

void UPuzzleUISubsystem::OpenPuzzleWidget(TSubclassOf<UWarUserWidget> UserWidgetClass)
{
	if (UserWidgetClass.Get() == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Please specify a user widget class to open the widget"));
		return;
	}

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), UserWidgetClass);
	Widget->AddToViewport();
}
