// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/WarCharacterBase.h"
#include "Interfaces/EnemyInterface.h"
#include "Character/CharacterClassInfo.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "WarEnemy.generated.h"

class UWidgetComponent;
class UBehaviorTree;
class AWarAIController;

/**
 * 
 */
UCLASS()
class MECHANICS_API AWarEnemy : public AWarCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:

	AWarEnemy();
	virtual void PossessedBy(AController* NewController) override;

	/**
	 * Combat interface
	 */
	virtual int32 GetPlayerLevel() override;
	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);
	virtual void Die() override;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	bool bHitReacting = false;

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	float BaseWalkSpeed = 250.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	float LifeSpan = 5.f;

protected:
	virtual void BeginPlay() override;
	void SetInitialValuesForWidget();
	void SetWidgetController();
	void BindToEvents();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	ECharacterClass CharacterClass = ECharacterClass::GenericBoxer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

	UPROPERTY(EditAnywhere, Category= "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<AWarAIController> WarAIController;
};
