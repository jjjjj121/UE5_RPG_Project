// Copyright Epic Games, Inc. All Rights Reserved.

#include "RPGGameGameMode.h"
#include "RPGGameCharacter.h"
#include "RPGGamePlayerController.h"
#include "RPGGamePlayerState.h"
#include "RPGGameHUD.h"
#include "UObject/ConstructorHelpers.h"

ARPGGameGameMode::ARPGGameGameMode()
{
	PlayerControllerClass = ARPGGamePlayerController::StaticClass();
	PlayerStateClass = ARPGGamePlayerState::StaticClass();
	

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/GameMode/BP_ModularCharacter"));
	if (PlayerPawnBPClass.Class != NULL){
		DefaultPawnClass = PlayerPawnBPClass.Class;	
	}
	
	//Blueprinted HUD class
	static ConstructorHelpers::FClassFinder<AHUD> PlayerHUDClass(TEXT("/Game/GameMode/BP_RPGGameHUD"));
	if (PlayerHUDClass.Class != NULL) {
		HUDClass = PlayerHUDClass.Class;
	}

}
