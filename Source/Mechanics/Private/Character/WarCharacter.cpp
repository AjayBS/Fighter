// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WarCharacter.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/WarAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Player/WarPlayerState.h"
#include "Player/WarPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "UI/HUD/WarHUD.h"
#include "WarGameplayTags.h"
#include "Components/CapsuleComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogWarCharacter, Error, All);

void AWarCharacter::BeginPlay()
{
	Super::BeginPlay();

	AWarPlayerState* WarPlayerState = GetPlayerState<AWarPlayerState>();
	if (WarPlayerState == nullptr)
	{
		return;
	}

	AWarPlayerController* WarPlayerController = Cast<AWarPlayerController>(GetController());
	if (WarPlayerController)
	{
		AWarHUD* WarHUD = Cast<AWarHUD>(WarPlayerController->GetHUD());
		if (WarHUD)
		{
			WarHUD->InitOverlay(WarPlayerController, WarPlayerState, Cast<UAbilitySystemComponent>(AbilitySystemComponent), AttributeSet);
		}
		else
		{
			UE_LOG(LogWarCharacter, Error, TEXT("Failed to get a valid HUD for player character."));
		}
	}
	else
	{
		UE_LOG(LogWarCharacter, Error, TEXT("Failed to get a valid player controller."));
	}

	AddCharacterAbilities();
	Super::InitializeDefaultAttributes();
	BindToEvents();
}

void AWarCharacter::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bHitReacting = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0 : BaseWalkSpeed;	
}

void AWarCharacter::BindToEvents()
{
	AbilitySystemComponent->RegisterGameplayTagEvent(FWarGameplayTags::Get().Effects_HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(
		this,
		&AWarCharacter::HitReactTagChanged
	);
}

AWarCharacter::AWarCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
}

void AWarCharacter::SetHitPauseEvent_Implementation()
{
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		this,
		FWarGameplayTags::Get().Player_Effects_HitPause,
		FGameplayEventData()
	);
}

int32 AWarCharacter::GetPlayerLevel()
{
	AWarPlayerState* WarPlayerState = GetPlayerState<AWarPlayerState>();
	check(WarPlayerState);
	return WarPlayerState->GetPlayerLevel();
}
