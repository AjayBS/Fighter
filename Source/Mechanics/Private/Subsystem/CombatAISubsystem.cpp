// Fill out your copyright notice in the Description page of Project Settings.

#include "Subsystem/CombatAISubsystem.h"

#include "Kismet/GameplayStatics.h"
#include "Mechanics/MechanicsGameMode.h"
#include "UI/Widget/DebugMeleeWidget.h"
#include "Components/WidgetComponent.h"
#include "Character/WarEnemy.h"

UCombatAISubsystem* UCombatAISubsystem::Get(const UWorld* InWorld)
{
	if (InWorld)
	{
		return InWorld->GetSubsystem<UCombatAISubsystem>();
	}

	return nullptr;
}

void UCombatAISubsystem::AddGradingAndUpdateWidget(AWarEnemy* Enemy)
{
	EnemyList.Add(Enemy);
	float Grading = FMath::RandRange(0.0f, 5.0f);
	EnemyGrading.Add(Enemy, Grading);

	AMechanicsGameMode* GameMode = Cast<AMechanicsGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (UDebugMeleeWidget* MeleeUI = CreateWidget<UDebugMeleeWidget>(GetWorld(), GameMode->DebugMeleeWidget))
	{
		MeleeUI->EnemyInstance = Enemy;
		MeleeUI->FightingGrade = Grading;

		Enemy->DebugWidgetComponent->SetWidget(MeleeUI);

	}
}

void UCombatAISubsystem::ResetGradingValues()
{
	for (auto& Pair : EnemyGrading)
	{
		Pair.Value = FMath::RandRange(0.0f, 5.0f);
		AWarEnemy* Enemy = Cast<AWarEnemy>(Pair.Key);

		if (UDebugMeleeWidget* MeleeUI = Cast<UDebugMeleeWidget>(Enemy->DebugWidgetComponent->GetWidget()))
		{
			MeleeUI->FightingGrade = Pair.Value;
		}
	}
}
