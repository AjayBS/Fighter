// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WarCharacter.h"

#include "Camera/CameraComponent.h"
#include "Player/WarPlayerState.h"
#include "Player/WarPlayerController.h"
#include "UI/HUD/WarHUD.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

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
			WarHUD->InitOverlay(WarPlayerController, WarPlayerState, AbilitySystemComponent, AttributeSet);
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
	CameraBoom->TargetArmLength = 400.0f; 
	CameraBoom->bUsePawnControlRotation = true; 

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); 
	FollowCamera->bUsePawnControlRotation = false;
}
