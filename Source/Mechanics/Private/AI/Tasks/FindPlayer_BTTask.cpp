// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/FindPlayer_BTTask.h"

#include "AI/WarAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

UFindPlayer_BTTask::UFindPlayer_BTTask()
{
	NodeName = "Find Player Location";
}

EBTNodeResult::Type UFindPlayer_BTTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	auto const Controller = Cast<AWarAIController>(OwnerComp.GetAIOwner());
	auto Blackboard = OwnerComp.GetBlackboardComponent();

	const FVector PlayerLocation = Player->GetActorLocation();
	if (SearchRandom)
	{
		FNavLocation Loc;

		const UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
		if (NavSys->GetRandomPointInNavigableRadius(PlayerLocation, SearchRadius, Loc, nullptr))
		{
			Blackboard->SetValueAsVector(TEXT("TargetLocation"), Loc.Location);
		}
	}
	else
	{
		Blackboard->SetValueAsVector(TEXT("TargetLocation"), PlayerLocation);
	}
	
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
