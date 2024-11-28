// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/WarHUD.h"
#include "UI/Widget/WarUserWidget.h"

void AWarHUD::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	Widget->AddToViewport();
}
