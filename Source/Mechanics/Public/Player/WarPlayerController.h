// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "GenericTeamAgentInterface.h"
#include "WarPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UWarInputConfig;
class UWarAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class MECHANICS_API AWarPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
	
public:
	AWarPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	// Begin IGenericTeamAgentInterface interface
	virtual FGenericTeamId GetGenericTeamId() const override;
	// End IGenericTeamAgentInterface interface

private:
	UWarAbilitySystemComponent* GetASC();

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> WarContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	void Move(const FInputActionValue& InputActionValue);
	void Look(const FInputActionValue& Value);

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UWarInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UWarAbilitySystemComponent> WarAbilitySystemComponent;

	FGenericTeamId WarTeamId;
};
