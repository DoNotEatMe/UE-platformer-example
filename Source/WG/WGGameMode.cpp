// Copyright Epic Games, Inc. All Rights Reserved.

#include "WGGameMode.h"
#include "WGCharacter.h"
#include "UObject/ConstructorHelpers.h"

AWGGameMode::AWGGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
