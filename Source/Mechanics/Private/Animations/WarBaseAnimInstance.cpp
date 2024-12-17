// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/WarBaseAnimInstance.h"

#include "WarBlueprintSystemLibrary.h"

bool UWarBaseAnimInstance::DoesOwnerHaveTag(FGameplayTag TagToCheck) const
{
	if (APawn* OwningPawn = TryGetPawnOwner())
	{
		return UWarBlueprintSystemLibrary::NativeDoesActorHaveTag(OwningPawn, TagToCheck);
	}

	return false;
}
