// Copyright Epic Games, Inc. All Rights Reserved.

#include "RPGGameGameMode.h"
#include "RPGGameCharacter.h"
#include "RPGGamePlayerController.h"
#include "RPGGamePlayerState.h"
#include "UObject/ConstructorHelpers.h"

ARPGGameGameMode::ARPGGameGameMode()
{
	PlayerControllerClass = ARPGGamePlayerController::StaticClass();
	PlayerStateClass = ARPGGamePlayerState::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/GameMode/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;	
	}

}
