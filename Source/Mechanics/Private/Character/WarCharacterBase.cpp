// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WarCharacterBase.h"

#include "AbilitySystem/WarAbilitySystemComponent.h"
#include "AbilitySystem/WarAttributeSet.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MotionWarpingComponent.h"
#include "WarGameplayTags.h"

AWarCharacterBase::AWarCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	AbilitySystemComponent = CreateDefaultSubobject<UWarAbilitySystemComponent>("AbilitySystemComponent");
	AttributeSet = CreateDefaultSubobject<UWarAttributeSet>("AttributeSet");
	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>("MotionWarpingComponent");
}

UAbilitySystemComponent* AWarCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AWarCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void AWarCharacterBase::AddCharacterAbilities()
{
	UWarAbilitySystemComponent* WarASC = Cast<UWarAbilitySystemComponent>(AbilitySystemComponent);

	WarASC->AddCharacterAbilities(StartupAbilities);
}

void AWarCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void AWarCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
}

void AWarCharacterBase::SetCombatTarget_Implementation(AActor* InCombatTarget)
{
	CombatTarget = InCombatTarget;
}

AActor* AWarCharacterBase::GetCombatTarget_Implementation() const
{
	return CombatTarget;
}

FVector AWarCharacterBase::GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag) const
{
	const FWarGameplayTags& GameplayTags = FWarGameplayTags::Get();
	
	for (int32 i = 0; i < AttackMontages.Num(); i++)
	{
		if (MontageTag.MatchesTagExact(AttackMontages[i].MontageTag))
		{
			return GetMesh()->GetSocketLocation(AttackMontages[i].SocketName);
		}
	}

	return FVector();
}


bool AWarCharacterBase::IsDead_Implementation() const
{
	return false;
}

AActor* AWarCharacterBase::GetAvatar_Implementation()
{
	return this;
}

TArray<FTaggedMontage> AWarCharacterBase::GetAttackMontages_Implementation()
{
	return AttackMontages;
}

UAnimMontage* AWarCharacterBase::GetHitReactMontage_Implementation()
{
	return HitReactMontage;
}

void AWarCharacterBase::Die()
{
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
