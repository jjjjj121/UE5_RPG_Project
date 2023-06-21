// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EWeaponEnum : uint8
{
	Hand			UMETA(DisplayName = "Hand"),
	GreatSword		UMETA(DisplayName = "GreatSword"),
	Sword			UMETA(DisplayName = "Sword"),
	Bow				UMETA(DisplayName = "Bow"),
};


class RPGGAME_API EnumHeader
{

public:
	EnumHeader();
	~EnumHeader();

};
