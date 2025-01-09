// Copyright ConfusedMinds Inc.


#include "Character/WarFlyingAI.h"

#include "AI/WarDroneAIController.h"

// Sets default values
AWarFlyingAI::AWarFlyingAI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PerceptionPoint = CreateDefaultSubobject<UStaticMeshComponent>("Perception Point");
	PerceptionPoint->SetupAttachment(RootComponent);
}
