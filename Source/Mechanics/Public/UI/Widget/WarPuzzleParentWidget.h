// Copyright ConfusedMinds Inc.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/WarUserWidget.h"
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
	UFUNCTION(BlueprintCallable)
	void CreateGrid(int32 RowLength, int32 ColumnLength);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UGridPanel> MainGridPanel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	TSubclassOf<UUserWidget> ButtonTemplateWidget;
	
};
