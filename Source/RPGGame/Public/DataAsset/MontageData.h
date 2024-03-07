// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Library/AnimEnumLibrary.h"

#include "MontageData.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API UMontageData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EMontageCategory, FAnimDataArray> MontageAnimList;

};
