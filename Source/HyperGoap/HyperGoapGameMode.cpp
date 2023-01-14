// Copyright Epic Games, Inc. All Rights Reserved.

#include "HyperGoapGameMode.h"
#include "HyperGoapCharacter.h"
#include "UObject/ConstructorHelpers.h"

AHyperGoapGameMode::AHyperGoapGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
