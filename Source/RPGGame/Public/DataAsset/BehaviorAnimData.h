// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "Library/AnimEnumLibrary.h"

#include "BehaviorAnimData.generated.h"

class ULocomotionData;
class UMontageData;


/*ĳ������ ��� �ൿ�� ���� Animation�� �����ϴ� DataAsset*/
/*Locomotion ���� Attack, React�� ���� Montage Play���� ���Ǵ� Animation ������*/

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
