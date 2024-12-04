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

void AWarCharacterBase::InitialzeDefaultAttributes() const
{
}

void AWarCharacterBase::HitDetection(float CollisionRadius, FName SocketName)
{
	TArray<AActor*> ActorsToIgnore;
	FHitResult HitResult;

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesArray;
	ObjectTypesArray.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel1));
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

