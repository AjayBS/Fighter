// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/FindPlayer_BTTask.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

UFindPlayer_BTTask::UFindPlayer_BTTask()
{
	NodeName = "Find Player";
}

EBTNodeResult::Type UFindPlayer_BTTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (Blackboard->GetValueAsObject(PlayerKey.SelectedKeyName) != nullptr)
	{
		return EBTNodeResult::Succeeded;
	}

	if (APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{		
		Blackboard->SetValueAsObject(PlayerKey.SelectedKeyName, Player);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
