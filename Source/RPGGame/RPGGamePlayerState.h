// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "RPGGame/Structs.h"
#include "RPGGamePlayerState.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API ARPGGamePlayerState : public APlayerState
{
	GENERATED_BODY()
	

public:
	UPROPERTY(BlueprintReadOnly, Category = "STATE")
		FRPGPlayerState State;

public:
	void UpdateHP(float TakeDamage);

};
