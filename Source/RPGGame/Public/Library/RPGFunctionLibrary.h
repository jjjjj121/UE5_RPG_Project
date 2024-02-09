// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RPGFunctionLibrary.generated.h"

class ARPGGameCharacter;
class ARPGGamePlayerController;
class URPGGameInstance;
class ARPGGamePlayerState;
class AItemActor;

/**
 * 
 */
UCLASS()
class RPGGAME_API URPGFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
#pragma region Player
public:
	UFUNCTION(BlueprintCallable, Meta = (WorldContext = "WorldContextObject"), Category = "Player")
		static ARPGGameCharacter* GetPlayerCharacter(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Meta = (WorldContext = "WorldContextObject"), Category = "Player")
		static ARPGGamePlayerController* GetPlayerController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Meta = (WorldContext = "WorldContextObject"), Category = "Player")
		static ARPGGamePlayerState* GetPlayerState(const UObject* WorldContextObject);

#pragma endregion

#pragma region Instance
public:
	UFUNCTION(BlueprintPure, Meta = (WorldContext = "WorldContextObject"), Category = "Instance")
		static URPGGameInstance* GetBOTWGameInstance(const UObject* WorldContextObject);

#pragma endregion

#pragma region Item
public:
	UFUNCTION(BlueprintPure, Meta = (WorldContext = "WorldContextObject"), Category = "Item")
		static AItemActor* SpawnItemtoPlayer(const UObject* WorldContextObject, FString ItemID, FName AttachSocket = TEXT(""));
#pragma endregion


};
