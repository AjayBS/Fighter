// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WarEnemy.h"

#include "AbilitySystem/WarAttributeSet.h"
#include "Components/WidgetComponent.h"
#include "WarBlueprintSystemLibrary.h"
#include "UI/Widget/WarUserWidget.h"

DEFINE_LOG_CATEGORY_STATIC(LogWarEnemyCharacter, Error, All);

AWarEnemy::AWarEnemy()
{
	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());
}

int32 AWarEnemy::GetPlayerLevel()
{
	return Level;
}

void AWarEnemy::BeginPlay()
{
	Super::BeginPlay();
	InitializeDefaultAttributes();
	BindToEvents();
	SetWidgetController();
	SetInitialValuesForWidget();
}

void AWarEnemy::SetInitialValuesForWidget()
{
	UWarAttributeSet* WarAS = CastChecked<UWarAttributeSet>(AttributeSet);
	if (WarAS)
	{
		OnHealthChanged.Broadcast(WarAS->GetHealth());
		OnMaxHealthChanged.Broadcast(WarAS->GetMaxHealth());
	}
	else
	{
		UE_LOG(LogWarEnemyCharacter, Warning, TEXT("Failed to get attribute set in enemy %s"), *GetName());
	}
}

void AWarEnemy::SetWidgetController()
{
	UWarUserWidget* WarUserWidget = Cast<UWarUserWidget>(HealthBar->GetUserWidgetObject());
	if (WarUserWidget)
	{
		WarUserWidget->SetWidgetController(this);
	}
	else
	{
		UE_LOG(LogWarEnemyCharacter, Warning, TEXT("Failed to get user widget in enemy %s"), *GetName());
	}
}

void AWarEnemy::BindToEvents()
{
	UWarAttributeSet* WarAS = CastChecked<UWarAttributeSet>(AttributeSet);
	if (WarAS)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(WarAS->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
		);

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(WarAS->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
		);		
	}
	else
	{
		UE_LOG(LogWarEnemyCharacter, Warning, TEXT("Failed to get attribute set in enemy %s"), *GetName());
	}
}
