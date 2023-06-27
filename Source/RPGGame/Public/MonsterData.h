// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MonsterData.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API UMonsterData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
		float Test;

public:
	UFUNCTION(BlueprintCallable)
	float TestFunc();

};
