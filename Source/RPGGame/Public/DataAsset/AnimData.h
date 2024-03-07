// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AnimData.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API UAnimData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<UAnimationAsset*> AnimAssetList;

	UPROPERTY(EditAnywhere)
	TArray<UAnimMontage*> MontageList;

};
