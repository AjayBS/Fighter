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

DEFINE_LOG_CATEGORY_STATIC(LogWarCharacter, Error, All);

void AWarCharacter::BeginPlay()
{
	Super::BeginPlay();

	AWarPlayerState* WarPlayerState = GetPlayerState<AWarPlayerState>();
	check(WarPlayerState);

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
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->MaxWalkSpeed = 200.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 400.f, 0.f);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 200.0f; 
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f);
	CameraBoom->bUsePawnControlRotation = true; 

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); 
	FollowCamera->bUsePawnControlRotation = false;
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
