// Copyright ConfusedMinds Inc.

#include "Actor/TogglePlayerMovementState.h"
#include "Components/BoxComponent.h"
#include "EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputMappingContext.h"

ATogglePlayerMovementState::ATogglePlayerMovementState()
{
	PrimaryActorTick.bCanEverTick = false;
	// Create Box Component
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));

    // Set its size and collision settings
    BoxComponent->InitBoxExtent(FVector(100.0f, 100.0f, 100.0f));
    BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    BoxComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
    BoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    BoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

    // Attach to Root
    RootComponent = BoxComponent;

    // Bind Overlap Event
    BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ATogglePlayerMovementState::OnBoxOverlap);
}

void ATogglePlayerMovementState::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != this)
    {
        ACharacter* Character = Cast<ACharacter>(OtherActor);
        if (Character != nullptr)
        {
            if (bShouldFly)
            {
                Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
                AddInputMapping(Character);                
            }
            else
            {
                Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
                RemoveInputMapping(Character);
            }

            BP_OperationsOnOverlap(bShouldFly);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Invalid type overlapped %s"), *OtherActor->GetName());
        }
    }
}

void ATogglePlayerMovementState::AddInputMapping(ACharacter* Character)
{
    if (Character == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to get a valid character."));
    }

    if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            if (MappingContext)
            {
                Subsystem->AddMappingContext(MappingContext, 1); // Priority 1
            }
        }
    }
}

void ATogglePlayerMovementState::RemoveInputMapping(ACharacter* Character)
{
    if (Character == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to get a valid character."));
    }

    if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            if (MappingContext)
            {
                Subsystem->RemoveMappingContext(MappingContext);
            }
        }
    }
}

void ATogglePlayerMovementState::BeginPlay()
{
	Super::BeginPlay();
	
}