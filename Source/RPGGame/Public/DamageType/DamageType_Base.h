// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "DamageType_Base.generated.h"


UENUM(BlueprintType)
enum class EDamageType : uint8
{
	Light,
	Normal,
	Heavy,
};

/**
 * 
 */
UCLASS()
class RPGGAME_API UDamageType_Base : public UDamageType
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	bool IsCharged = false;

	UPROPERTY(EditAnywhere)
	EDamageType DamageType;
};
