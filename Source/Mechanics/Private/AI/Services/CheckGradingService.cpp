// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/CheckGradingService.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Subsystem/CombatAISubsystem.h"

void UCheckGradingService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (UCombatAISubsystem* CombatAISubsystem = UCombatAISubsystem::Get(GetWorld()))
	{
		AActor* HighestGradedActor = nullptr;
		float HighestGrade = 0.f;
		for (const TPair<AActor*, float>& Pair : CombatAISubsystem->EnemyGrading)
		{
			if (HighestGrade <= Pair.Value)
			{
				HighestGrade = Pair.Value;
				HighestGradedActor = Pair.Key;
			}
		}

		bool bIsOwner = OwnerComp.GetOwner() == HighestGradedActor->GetOwner();
		Blackboard->SetValueAsBool(bIsHighestGraded.SelectedKeyName, bIsOwner);
	}
}
