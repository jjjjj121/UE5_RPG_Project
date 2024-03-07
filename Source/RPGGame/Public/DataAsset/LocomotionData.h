// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Library/AnimEnumLibrary.h"
#include "LocomotionData.generated.h"


UCLASS(BlueprintType)
class RPGGAME_API ULocomotionData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<ELocomotionCategory, FAnimDataArray> LocomotionAnimList;
};
