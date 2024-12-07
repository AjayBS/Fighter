// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WarCharacterBase.h"

#include "AbilitySystem/WarAbilitySystemComponent.h"
#include "AbilitySystem/WarAttributeSet.h"
#include "Kismet/KismetSystemLibrary.h"

AWarCharacterBase::AWarCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	AbilitySystemComponent = CreateDefaultSubobject<UWarAbilitySystemComponent>("AbilitySystemComponent");
	AttributeSet = CreateDefaultSubobject<UWarAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* AWarCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AWarCharacterBase::HitDetection(float CollisionRadius, FName SocketName)
{
	TArray<AActor*> ActorsToIgnore;
	FHitResult HitResult;

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesArray;
	ObjectTypesArray.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
	ActorsToIgnore.Add(this);
	bool bHasHit = UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), 
	GetMesh()->GetSocketLocation(SocketName),
	GetMesh()->GetSocketLocation(SocketName),
	CollisionRadius,
	ObjectTypesArray, 
	false,
	ActorsToIgnore,
	EDrawDebugTrace::ForDuration, 
	HitResult, 
	true);

	if (bHasHit)
	{
		// Handle the hit result
		UE_LOG(LogTemp, Warning, TEXT("Hit actor: %s"), *HitResult.GetActor()->GetName());
	}
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
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
}

void AWarCharacterBase::SetCombatTarget_Implementation(AActor* InCombatTarget)
{
	CombatTarget = InCombatTarget;
}

AActor* AWarCharacterBase::GetCombatTarget_Implementation() const
{
	return CombatTarget;
}

FVector AWarCharacterBase::GetCombatSocketLocation_Implementation() const
{
	return bLeftHanded ? GetMesh()->GetSocketLocation("hand_l") : GetMesh()->GetSocketLocation("hand_r");
}

bool AWarCharacterBase::IsLeftHandedAttack_Implementation()
{
	return bLeftHanded;
}

void AWarCharacterBase::SetIsLeftHandedAttack_Implementation(bool bLeftHand)
{
	bLeftHanded = bLeftHand;
}


bool AWarCharacterBase::IsDead_Implementation() const
{
	return false;
}

AActor* AWarCharacterBase::GetAvatar_Implementation()
{
	return this;
}
