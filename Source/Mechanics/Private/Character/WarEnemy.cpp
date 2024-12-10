// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WarEnemy.h"

#include "AbilitySystem/WarAttributeSet.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UI/Widget/WarUserWidget.h"
#include "WarBlueprintSystemLibrary.h"
#include "WarGameplayTags.h"


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

void AWarEnemy::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bHitReacting = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0 : BaseWalkSpeed;
}

void AWarEnemy::BeginPlay()
{
	Super::BeginPlay();
	InitializeDefaultAttributes();
	BindToEvents();
	SetWidgetController();
	SetInitialValuesForWidget();

	UWarBlueprintSystemLibrary::GiveStartupAbilities(this, AbilitySystemComponent, CharacterClass);
	UWarBlueprintSystemLibrary::InitializeDefaultAttributes(this, AbilitySystemComponent, CharacterClass, Level);
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
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

		
		AbilitySystemComponent->RegisterGameplayTagEvent(FWarGameplayTags::Get().Effects_HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(
			this,
			&AWarEnemy::HitReactTagChanged
		);
	}
	else
	{
		UE_LOG(LogWarEnemyCharacter, Warning, TEXT("Failed to get attribute set in enemy %s"), *GetName());
	}
}
