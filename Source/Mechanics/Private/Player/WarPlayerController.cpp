// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/WarPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/WarAbilitySystemComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Input/WarInputComponent.h"
#include "Kismet/KismetMathLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(LogWarPlayerController, Error, All);

AWarPlayerController::AWarPlayerController()
{
	bReplicates = true;
}

void AWarPlayerController::BeginPlay()
{	
	Super::BeginPlay();
	check(WarContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(WarContext, 0);

	WarTeamId = FGenericTeamId(0);
}

void AWarPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UWarInputComponent* WarInputComponent = CastChecked<UWarInputComponent>(InputComponent);
	WarInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AWarPlayerController::Move);
	WarInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AWarPlayerController::Look);
	WarInputComponent->BindAction(SpaceWalkAction, ETriggerEvent::Triggered, this, &AWarPlayerController::SpaceWalk);

	WarInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

FGenericTeamId AWarPlayerController::GetGenericTeamId() const
{
	return WarTeamId;
}

void AWarPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	// find out which way is forward
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get forward vector
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	// get right vector 
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	APawn* ControlledPawn = GetPawn<APawn>();
	if (ControlledPawn)
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}	
}

void AWarPlayerController::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	APawn* ControlledPawn = GetPawn<APawn>();
	if (ControlledPawn)
	{
		ControlledPawn->AddControllerYawInput(LookAxisVector.X);
		ControlledPawn->AddControllerPitchInput(LookAxisVector.Y);
	}

	BP_UpdateTargetingData(LookAxisVector);
}

void AWarPlayerController::SpaceWalk(const FInputActionValue& Value)
{
	float ActionValue = Value.Get<float>();

	APawn* ControlledPawn = GetPawn<APawn>();
	if (ControlledPawn)
	{
		FVector ForwardVector = UKismetMathLibrary::GetForwardVector(ControlledPawn->GetControlRotation()) * 0.001f;
		ControlledPawn->AddMovementInput(FVector(ForwardVector.X, ForwardVector.Y, ActionValue), FMath::Abs(ActionValue));
	}
}

void AWarPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (GetASC() == nullptr)
	{
		UE_LOG(LogWarPlayerController, Error, TEXT("AbilitySystemComponent is null in player controller"));
		return;
	}

	GetASC()->AbilityInputTagPressed(InputTag);
}

void AWarPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (GetASC() == nullptr)
	{
		UE_LOG(LogWarPlayerController, Error, TEXT("AbilitySystemComponent is null in player controller"));
		return;
	}

	GetASC()->AbilityInputTagReleased(InputTag);
}

void AWarPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (GetASC() == nullptr)
	{
		UE_LOG(LogWarPlayerController, Error, TEXT("AbilitySystemComponent is null in player controller"));
		return;
	}

	GetASC()->AbilityInputTagHeld(InputTag);
}

UWarAbilitySystemComponent* AWarPlayerController::GetASC()
{
	if (WarAbilitySystemComponent == nullptr)
	{
		WarAbilitySystemComponent = Cast<UWarAbilitySystemComponent>(
			UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}

	return WarAbilitySystemComponent;
}
