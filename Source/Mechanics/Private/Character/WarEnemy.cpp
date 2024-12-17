// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WarEnemy.h"

#include "AbilitySystem/WarAttributeSet.h"
#include "AI/WarAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Subsystem/CombatAISubsystem.h"
#include "UI/Widget/WarUserWidget.h"
#include "WarBlueprintSystemLibrary.h"
#include "WarGameplayTags.h"

DEFINE_LOG_CATEGORY_STATIC(LogWarEnemyCharacter, Error, All);

AWarEnemy::AWarEnemy()
{
	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());

	DebugWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("DebugMelee");
	DebugWidgetComponent->SetupAttachment(GetRootComponent());
}

void AWarEnemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	WarAIController = Cast<AWarAIController>(NewController);

	if (BehaviorTree != nullptr)
	{
		WarAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
		WarAIController->RunBehaviorTree(BehaviorTree);
	}
	else
	{
		UE_LOG(LogWarEnemyCharacter, Warning, TEXT("No behavior tree set for enemy %s"), *GetName());
	}
	
	WarAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), false);
}

void AWarEnemy::Destroyed()
{
	if (UCombatAISubsystem* CombatAISubsystem = UCombatAISubsystem::Get(GetWorld()))
	{
		CombatAISubsystem->EnemyList.Remove(this);
	}
}

int32 AWarEnemy::GetPlayerLevel()
{
	return Level;
}

void AWarEnemy::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bHitReacting = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0 : BaseWalkSpeed;
	WarAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), bHitReacting);
}

void AWarEnemy::Die()
{
	SetLifeSpan(LifeSpan);
	Super::Die();
}

void AWarEnemy::BeginPlay()
{
	Super::BeginPlay();

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 180.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;

	InitializeDefaultAttributes();
	BindToEvents();
	SetWidgetController();
	SetInitialValuesForWidget();

	UWarBlueprintSystemLibrary::GiveStartupAbilities(this, AbilitySystemComponent, CharacterClass);
	UWarBlueprintSystemLibrary::InitializeDefaultAttributes(this, AbilitySystemComponent, CharacterClass, Level);
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;

	if (UCombatAISubsystem* CombatAISubsystem = UCombatAISubsystem::Get(GetWorld()))
	{
		CombatAISubsystem->AddGradingAndUpdateWidget(this);
	}
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
