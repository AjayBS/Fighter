// Fill out your copyright notice in the Description page of Project Settings.


#include "WarBlueprintSystemLibrary.h"

#include "AbilitySystem/WarAbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Player/WarPlayerController.h"
#include "Mechanics/MechanicsGameMode.h"
#include "AbilitySystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Interfaces/CombatInterface.h"
#include "Character/CharacterClassInfo.h"
#include "GameplayEffectTypes.h"
#include "Engine/OverlapResult.h"
#include "Kismet/KismetMathLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(LogWarBlueprintLibrary, Warning, All);

UWarAbilitySystemComponent* UWarBlueprintSystemLibrary::NativeGetWarASCFromActor(AActor* InActor)
{
	check(InActor);

	return CastChecked<UWarAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

void UWarBlueprintSystemLibrary::GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, ECharacterClass CharacterClass)
{
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	if (CharacterClassInfo == nullptr) return;
	for (TSubclassOf<UGameplayAbility> AbilityClass : CharacterClassInfo->CommonAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		ASC->GiveAbility(AbilitySpec);
	}
}

UCharacterClassInfo* UWarBlueprintSystemLibrary::GetCharacterClassInfo(const UObject* WorldContextObject)
{
	AMechanicsGameMode* WarGameMode = Cast<AMechanicsGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (WarGameMode == nullptr) 
	{
		return nullptr;
	}
	return WarGameMode->CharacterClassInfo;
}

void UWarBlueprintSystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, ECharacterClass CharacterClass, float Level)
{
	AMechanicsGameMode* WarGameMode = Cast<AMechanicsGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (WarGameMode == nullptr)
	{
		UE_LOG(LogWarBlueprintLibrary, Warning, TEXT("Game mode is nullptr. Returning."));
		return;
	}

	FCharacterClassDefaultInfo ClassDefaultInfo = WarGameMode->CharacterClassInfo->GetClassDefaultInfo(CharacterClass);	
	
	const FGameplayEffectSpecHandle PrimaryAttributesSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttributes, Level, ASC->MakeEffectContext());
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data.Get());

	const FGameplayEffectSpecHandle SecondaryAttributesSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.SecondaryAttributes, Level, ASC->MakeEffectContext());
	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributesSpecHandle.Data.Get());
}

void UWarBlueprintSystemLibrary::GetLivePlayersWithinRadius(const UObject* WorldContextObject, TArray<AActor*>& OutOverlappingActors, 
	const TArray<AActor*>& ActorsToIgnore, 
	float Radius, const FVector& SphereOrigin)
{
	FCollisionQueryParams SphereParams;
	SphereParams.AddIgnoredActors(ActorsToIgnore);

	TArray<FOverlapResult> Overlaps;
	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		World->OverlapMultiByObjectType(Overlaps, SphereOrigin, FQuat::Identity, 
			FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllDynamicObjects), 
			FCollisionShape::MakeSphere(Radius), SphereParams);

		for (FOverlapResult& Overlap : Overlaps)
		{
			const bool ImplementsCombatInterface = Overlap.GetActor()->Implements<UCombatInterface>();

			// TO-DO Check for is dead.

			if (ImplementsCombatInterface)
			{
				OutOverlappingActors.AddUnique(ICombatInterface::Execute_GetAvatar(Overlap.GetActor()));
			}
		}
	}
}

void UWarBlueprintSystemLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
	UWarAbilitySystemComponent* ASC = NativeGetWarASCFromActor(InActor);

	if (!ASC->HasMatchingGameplayTag(TagToAdd))
	{
		ASC->AddLooseGameplayTag(TagToAdd);
	}
}

void UWarBlueprintSystemLibrary::RemoveGameplayFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
	UWarAbilitySystemComponent* ASC = NativeGetWarASCFromActor(InActor);

	if (ASC->HasMatchingGameplayTag(TagToRemove))
	{
		ASC->RemoveLooseGameplayTag(TagToRemove);
	}
}

bool UWarBlueprintSystemLibrary::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
	if (InActor != nullptr)
	{
		UWarAbilitySystemComponent* ASC = NativeGetWarASCFromActor(InActor);
		return ASC->HasMatchingGameplayTag(TagToCheck);
	}
	
	return false;
}

void UWarBlueprintSystemLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EWarConfirmType& OutConfirmType)
{
	OutConfirmType = NativeDoesActorHaveTag(InActor, TagToCheck) ? EWarConfirmType::Yes : EWarConfirmType::No;
}

bool UWarBlueprintSystemLibrary::IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn)
{
	check(QueryPawn && TargetPawn);

	IGenericTeamAgentInterface* QueryTeamAgent = Cast<IGenericTeamAgentInterface>(QueryPawn->GetController());
	IGenericTeamAgentInterface* TargetTeamAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());

	if (QueryTeamAgent && TargetTeamAgent)
	{
		return QueryTeamAgent->GetGenericTeamId() != TargetTeamAgent->GetGenericTeamId();
	}

	return false;
}

FGameplayTag UWarBlueprintSystemLibrary::ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim, float& OutAngleDifference)
{
	check(InAttacker && InVictim);

	const FVector VictimForward = InVictim->GetActorForwardVector();
	const FVector VictimToAttackerNormalized = (InAttacker->GetActorLocation() - InVictim->GetActorLocation().GetSafeNormal());

	const float DotResult = FVector::DotProduct(VictimForward, VictimToAttackerNormalized);
	OutAngleDifference = UKismetMathLibrary::DegAcos(DotResult);

	return FGameplayTag();
}
