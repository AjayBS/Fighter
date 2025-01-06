// Copyright ConfusedMinds Inc.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "PuzzleUISubsystem.generated.h"

UENUM(BlueprintType)
enum class EColorCodes : uint8
{
	None,
	Blue,
	Green,
	Yellow,
	Red
};

USTRUCT(BlueprintType)
struct FTileInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile Info")
	EColorCodes Color;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile Info")
	int32 Row;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile Info")
	int32 Column;

	bool operator== (const FTileInfo& Other)
	{
		return Row == Other.Row && Column == Other.Column;
	}

	FTileInfo(EColorCodes InColor, int32 InRow, int32 InColumn)
		: Color(InColor), Row(InRow), Column(InColumn) { }

	FTileInfo() 
		: Color(EColorCodes::None), Row(0), Column(0)
	{}

};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPuzzleCompleted, UWarUserWidget*, UserWidget);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FPuzzleOperation, int32, Row, int32, Column, bool, bSelected);

class UWarUserWidget;

/**
 * 
 */
UCLASS()
class MECHANICS_API UPuzzleUISubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	static UPuzzleUISubsystem* Get(const UWorld* InWorld);

	UFUNCTION(BlueprintCallable)
	void OpenPuzzleWidget(TSubclassOf<UWarUserWidget> UserWidgetClass);

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FPuzzleOperation TileActivated;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FPuzzleCompleted PuzzleCompleted;
	
};
