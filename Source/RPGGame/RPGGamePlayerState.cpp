// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGGamePlayerState.h"
#include "Math/UnrealMathUtility.h"

void ARPGGamePlayerState::UpdateHP(float TakeDamage)
{
	CurHP = FMath::Clamp<float>(CurHP - TakeDamage, 0, MaxHP);
	UE_LOG(LogTemp, Warning, TEXT("CUR HP : %f"), CurHP);

}
