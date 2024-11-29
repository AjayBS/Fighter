// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/WarPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "Input/WarInputComponent.h"

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
}

void AWarPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UWarInputComponent* AuraInputComponent = CastChecked<UWarInputComponent>(InputComponent);
	AuraInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AWarPlayerController::Move);
	AuraInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AWarPlayerController::Look);

	AuraInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
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
}

void AWarPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Red, *InputTag.ToString());
}

void AWarPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	GEngine->AddOnScreenDebugMessage(2, 3.f, FColor::Blue, *InputTag.ToString());
}

void AWarPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	GEngine->AddOnScreenDebugMessage(4, 3.f, FColor::Green, *InputTag.ToString());
}
