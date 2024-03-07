// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/BehaviorAnimData.h"
#include "DataAsset/MontageData.h"
#include "DataAsset/LocomotionData.h"

FAnimDataArray UBehaviorAnimData::GetLocomotionList(ELocomotionCategory Category)
{
    return Locomotion->LocomotionAnimList[Category];
}

FAnimDataArray UBehaviorAnimData::GetMontageList(EMontageCategory Category)
{
    return Montage->MontageAnimList[Category];
}
