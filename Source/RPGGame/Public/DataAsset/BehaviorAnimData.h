// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "Library/AnimEnumLibrary.h"

#include "BehaviorAnimData.generated.h"

class ULocomotionData;
class UMontageData;


/*캐릭터의 모든 행동에 대한 Animation을 저장하는 DataAsset*/
/*Locomotion 부터 Attack, React와 같은 Montage Play까지 사용되는 Animation 데이터*/

UCLASS(BlueprintType, Const)
class RPGGAME_API UBehaviorAnimData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locomotion Anim")
	ULocomotionData* Locomotion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage Play Anim")
	UMontageData* Montage;

public:
	FAnimDataArray GetLocomotionList(ELocomotionCategory Category);
	FAnimDataArray GetMontageList(EMontageCategory Category);

};
