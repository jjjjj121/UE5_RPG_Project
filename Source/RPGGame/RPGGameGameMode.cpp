// Copyright Epic Games, Inc. All Rights Reserved.

#include "RPGGameGameMode.h"
#include "RPGGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARPGGameGameMode::ARPGGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
