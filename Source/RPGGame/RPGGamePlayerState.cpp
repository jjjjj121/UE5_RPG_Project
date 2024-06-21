// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGGamePlayerState.h"
#include "Math/UnrealMathUtility.h"

void ARPGGamePlayerState::UpdateHP(float TakeDamage)
{
	State.CurHP = FMath::Clamp<float>(State.CurHP - TakeDamage, 0, State.MaxHP);
	UE_LOG(LogTemp, Warning, TEXT("CUR HP : %f"), State.CurHP);

}
