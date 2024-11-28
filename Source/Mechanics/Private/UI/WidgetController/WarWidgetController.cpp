// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/WarWidgetController.h"

void UWarWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UWarWidgetController::BroadcastInitialValues()
{
}

void UWarWidgetController::BindCallbacksToDependencies()
{
}
