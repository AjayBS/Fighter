// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/WarCharacterBase.h"
#include "WarCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

/**
 * 
 */
UCLASS()
class MECHANICS_API AWarCharacter : public AWarCharacterBase
{
	GENERATED_BODY()

private:
	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	// Begin ICombat interface
	virtual void SetHitPauseEvent_Implementation() override;
	// End ICombat interface

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	float BaseWalkSpeed = 250.f;

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	bool bHitReacting = false;

	virtual void BeginPlay() override;
	void BindToEvents();

public:
	AWarCharacter();

	/**
	 * Combat interface
	 */

	 virtual int32 GetPlayerLevel() override;
	 virtual bool IsAI_Implementation() const override { return false; }
};
