// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/WarCharacterBase.h"
#include "Interfaces/EnemyInterface.h"
#include "Character/CharacterClassInfo.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "WarEnemy.generated.h"

class UWidgetComponent;

/**
 * 
 */
UCLASS()
class MECHANICS_API AWarEnemy : public AWarCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:

	AWarEnemy();
	/**
	 * Combat interface
	 */
	 virtual int32 GetPlayerLevel() override;

	 UPROPERTY(BlueprintAssignable)
	 FOnAttributeChangedSignature OnHealthChanged;

	 UPROPERTY(BlueprintAssignable)
	 FOnAttributeChangedSignature OnMaxHealthChanged;

protected:	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	ECharacterClass CharacterClass = ECharacterClass::Elementalist;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

	virtual void BeginPlay() override;
	void SetInitialValuesForWidget();
	void SetWidgetController();
	void BindToEvents();
};
