// Copyright ConfusedMinds Inc.


#include "AI/Services/BTS_DistanceToTarget.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Debug/WarDebugHelper.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

UBTS_DistanceToTarget::UBTS_DistanceToTarget()
{
	NodeName = TEXT("Native distance to target actor.");

	INIT_SERVICE_NODE_NOTIFY_FLAGS();
}

void UBTS_DistanceToTarget::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	if (UBlackboardData* BBAsset = GetBlackboardAsset())
	{
		InIsCloseEnough.ResolveSelectedKey(*BBAsset);
	}
}

FString UBTS_DistanceToTarget::GetStaticDescription() const
{
	return FString::Printf(TEXT("Target distance to player %s"), *GetStaticServiceDescription());
}

void UBTS_DistanceToTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	const ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	APawn* OwningPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (OwningPawn && Player)
	{
		float DistanceToTarget = FVector::Dist(OwningPawn->GetActorLocation(), Player->GetActorLocation());
		Debug::Print(FString::SanitizeFloat(DistanceToTarget));
		if (DistanceToTarget < DistanceThreshold)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(InIsCloseEnough.SelectedKeyName, true);
		}
		else
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(InIsCloseEnough.SelectedKeyName, false);
		}
	}
}
