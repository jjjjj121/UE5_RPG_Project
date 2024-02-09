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

/*ĳ������ ��� �ൿ�� ���� Animation�� �����ϴ� DataAsset*/
/*Locomotion ���� Attack, React�� ���� Montage Play���� ���Ǵ� Animation ������*/

UCLASS(BlueprintType, Const)
class RPGGAME_API UBehaviorAnimData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locomotion Anim")
	ULocomotionData* Locomotion;

};
