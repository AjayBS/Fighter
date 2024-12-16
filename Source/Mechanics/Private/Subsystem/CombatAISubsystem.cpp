// Fill out your copyright notice in the Description page of Project Settings.

#include "Subsystem/CombatAISubsystem.h"

#include "Kismet/GameplayStatics.h"
#include "Mechanics/MechanicsGameMode.h"
#include "UI/Widget/DebugMeleeWidget.h"
#include "Components/WidgetComponent.h"
#include "Character/WarEnemy.h"
#include "Kismet/KismetMathLibrary.h"

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
	float Grading = SetScoreBasedOnDirection(Enemy);
	EnemyGrading.Add(Enemy, Grading);

	AMechanicsGameMode* GameMode = Cast<AMechanicsGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (UDebugMeleeWidget* MeleeUI = CreateWidget<UDebugMeleeWidget>(GetWorld(), GameMode->DebugMeleeWidget))
	{
		MeleeUI->EnemyInstance = Enemy;
		MeleeUI->FightingGrade = Grading;

		Enemy->DebugWidgetComponent->SetWidget(MeleeUI);
	}
}

float UCombatAISubsystem::SetScoreBasedOnDirection(AWarEnemy* Enemy)
{
	float Grading = 0.f;
	FVector EnemyForwardVector = Enemy->GetActorForwardVector();
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	FVector PlayerForwardVector = Player->GetActorForwardVector();

	float DotProd = FVector::DotProduct(EnemyForwardVector, PlayerForwardVector);
	DotProd *= -1.f;
	float NormalizedValue = UKismetMathLibrary::NormalizeToRange(DotProd, -1.f, 1.f);
	NormalizedValue += 0.5f;
	Grading *= NormalizedValue;

	return Grading;
}

void UCombatAISubsystem::ResetGradingValues()
{
	for (auto& Pair : EnemyGrading)
	{
		Pair.Value = FMath::RandRange(0.0f, 5.0f);
		AWarEnemy* Enemy = Cast<AWarEnemy>(Pair.Key);

		if (Enemy != nullptr)
		{
			if (UDebugMeleeWidget* MeleeUI = Cast<UDebugMeleeWidget>(Enemy->DebugWidgetComponent->GetWidget()))
			{
				MeleeUI->FightingGrade = Pair.Value;
			}
		}		
	}
}
