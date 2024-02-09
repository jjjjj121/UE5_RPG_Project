// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BehaviorAnimData.generated.h"

class UAnimData;
class ULocomotionData;

UENUM(BlueprintType)
enum class EBehaviorCategory : uint8
{
	Default,
	Attack,
	React,
	Death,
};

/*캐릭터의 모든 행동에 대한 Animation을 저장하는 DataAsset*/
/*Locomotion 부터 Attack, React와 같은 Montage Play까지 사용되는 Animation 데이터*/

UCLASS(BlueprintType, Const)
class RPGGAME_API UBehaviorAnimData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locomotion Anim")
	ULocomotionData* Locomotion;

};
