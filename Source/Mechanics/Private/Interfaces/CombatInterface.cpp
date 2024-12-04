// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/CombatInterface.h"

// Add default functionality here for any ICombatInterface functions that are not pure virtual.

AActor* ICombatInterface::GetAvatar()
{
    return nullptr;
}

int32 ICombatInterface::GetPlayerLevel()
{
    return 0;
}
