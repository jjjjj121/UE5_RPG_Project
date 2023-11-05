// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
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
		float MaxHP = 100;

	UPROPERTY(BlueprintReadOnly, Category = "STATE")
		float MaxMP;

	UPROPERTY(BlueprintReadOnly, Category = "STATE")
		float CurHP = 100;

	UPROPERTY(BlueprintReadOnly, Category = "STATE")
		float CurMP;

	UPROPERTY(BlueprintReadOnly, Category = "STATE")
		float Damage = 10;

public:
	void UpdateHP(float TakeDamage);

};
