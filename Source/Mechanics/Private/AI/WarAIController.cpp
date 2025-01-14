// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/WarAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Interfaces/PlayerInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"

DEFINE_LOG_CATEGORY_STATIC(LogWarAIController, Error, All);

AWarAIController::AWarAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>("PathFollowingComponent"))
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>("BlackboardComponent");
	check(Blackboard);
	BehavioreTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviorTreeComponent");
	check(BehavioreTreeComponent);

	AISenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("EnemySenseConfig_Sight");
	AISenseConfig_Sight->DetectionByAffiliation.bDetectEnemies = true;
	AISenseConfig_Sight->DetectionByAffiliation.bDetectFriendlies = true;
	AISenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = true;
	AISenseConfig_Sight->SightRadius = 500.f;
	AISenseConfig_Sight->PeripheralVisionAngleDegrees = 90.f;
	AISenseConfig_Sight->SetMaxAge(5.0f);

	AISenseConfig_Hearing = CreateDefaultSubobject<UAISenseConfig_Hearing>("EnemySenseConfig_Hearing");
	AISenseConfig_Hearing->HearingRange = 3000.0f;
	AISenseConfig_Hearing->DetectionByAffiliation.bDetectEnemies = true;
	AISenseConfig_Hearing->DetectionByAffiliation.bDetectNeutrals = true;
	AISenseConfig_Hearing->DetectionByAffiliation.bDetectFriendlies = true;
	AISenseConfig_Hearing->SetMaxAge(35.0f);

	EnemyPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("EnemyPerceptionComponent");
	EnemyPerceptionComponent->ConfigureSense(*AISenseConfig_Sight);
	EnemyPerceptionComponent->ConfigureSense(*AISenseConfig_Hearing);
	EnemyPerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());
	EnemyPerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &ThisClass::OnEnemyPerceptionUpdated);

	SetGenericTeamId(FGenericTeamId(1));
}

ETeamAttitude::Type AWarAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	const APawn* PawnToCheck = Cast<const APawn>(&Other);
	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<IGenericTeamAgentInterface>(PawnToCheck->GetController());

	if (OtherTeamAgent && OtherTeamAgent->GetGenericTeamId() < GetGenericTeamId())
	{
		return ETeamAttitude::Hostile;
	}

	return ETeamAttitude::Friendly;
}

void AWarAIController::BeginPlay()
{
	Super::BeginPlay();

	if (UCrowdFollowingComponent* CrowdComp = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
	{
		CrowdComp->SetCrowdSimulationState(bEnableDetourCrowdAvoidance ? ECrowdSimulationState::Enabled : ECrowdSimulationState::Disabled);

		switch (DetourCrowdAvoidanceQuality)
		{
		case 1: CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Low);		break;
		case 2: CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Medium);	break;
		case 3: CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Good);		break;
		case 4: CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::High);		break;
		default:
			break;
		}

		CrowdComp->SetAvoidanceGroup(1);
		CrowdComp->SetGroupsToAvoid(1);
		CrowdComp->SetCrowdCollisionQueryRange(CollisionQueryRange);
	}
}

void AWarAIController::OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (UBlackboardComponent* BlackboardComponent = GetBlackboardComponent())
	{
		if (Actor->GetClass()->ImplementsInterface(UPlayerInterface::StaticClass()))
		{
			// Get the Sense ID for sight and hearing
			FAISenseID SightSenseID = UAISense::GetSenseID<UAISense_Sight>();
			FAISenseID HearingSenseID = UAISense::GetSenseID<UAISense_Hearing>();

			if (Stimulus.Type == HearingSenseID)
			{
				BlackboardComponent->SetValueAsBool(FName("HasHeardNoise"), Stimulus.WasSuccessfullySensed());
			}

			float DetectionValue = 0.f;
			if (Stimulus.Type == SightSenseID)
			{
				float Dist = FVector::Distance(Stimulus.StimulusLocation, Stimulus.ReceiverLocation);
				float Range = UKismetMathLibrary::NormalizeToRange(Dist, 0.f, 500.f);
				DetectionValue = SightCurve->GetFloatValue(Range);
				BlackboardComponent->SetValueAsBool(FName("HasSeenPlayer"), Stimulus.WasSuccessfullySensed());
				SenseDetection.Broadcast(Stimulus.WasSuccessfullySensed(), DetectionValue);
			}

			BlackboardComponent->SetValueAsVector(TEXT("TargetLocation"), Stimulus.StimulusLocation);
		}
	}	
}