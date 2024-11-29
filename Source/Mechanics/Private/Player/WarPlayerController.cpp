// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/WarPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/WarAbilitySystemComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Input/WarInputComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogWarCharacter, Error, All);

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
	//GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Red, *InputTag.ToString());
}

void AWarPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (GetASC() == nullptr)
	{
		UE_LOG(LogWarCharacter, Error, TEXT("AbilitySystemComponent is null in player controller"));
		return;
	}

	GetASC()->AbilityInputTagReleased(InputTag);
}

void AWarPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (GetASC() == nullptr)
	{
		UE_LOG(LogWarCharacter, Error, TEXT("AbilitySystemComponent is null in player controller"));
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
