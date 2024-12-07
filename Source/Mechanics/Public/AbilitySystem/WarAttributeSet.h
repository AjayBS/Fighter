// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "WarAttributeSet.generated.h"

DEFINE_LOG_CATEGORY_STATIC(LogWarAttributeSet, Error, All);

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class MECHANICS_API UWarAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UWarAttributeSet();

	/**
	 * Primary Attributes
	 */

	UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UWarAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UWarAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UWarAttributeSet, Stamina);

	UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UWarAttributeSet, MaxStamina);

	UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UWarAttributeSet, Armor);

	/**
	 * Secondary Attributes
	 */

	UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData Potion;
	ATTRIBUTE_ACCESSORS(UWarAttributeSet, Potion);

	UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UWarAttributeSet, Vigor);

	UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS(UWarAttributeSet, BlockChance);

	UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData EnergyBar;
	ATTRIBUTE_ACCESSORS(UWarAttributeSet, EnergyBar);

	UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData ChocoBar;
	ATTRIBUTE_ACCESSORS(UWarAttributeSet, ChocoBar);

	UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData Shards;
	ATTRIBUTE_ACCESSORS(UWarAttributeSet, Shards);

	UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData CritHit;
	ATTRIBUTE_ACCESSORS(UWarAttributeSet, CritHit);

	/**
	 * Meta attributes
	 */

	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(UWarAttributeSet, IncomingDamage);

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
};
