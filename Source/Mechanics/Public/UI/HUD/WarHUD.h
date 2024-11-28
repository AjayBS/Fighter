// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "WarHUD.generated.h"

class UWarUserWidget;

/**
 * 
 */
UCLASS()
class MECHANICS_API AWarHUD : public AHUD
{
	GENERATED_BODY()

public:	
	UPROPERTY()
	TObjectPtr<UWarUserWidget> OverlayWidget;

protected:
	virtual void BeginPlay();

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UWarUserWidget> OverlayWidgetClass;
};
