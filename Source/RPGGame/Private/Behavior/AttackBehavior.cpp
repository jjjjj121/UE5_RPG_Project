// Fill out your copyright notice in the Description page of Project Settings.


#include "Behavior/AttackBehavior.h"


void UAttackBehavior::PlayAttackMontage()
{
	//UE_LOG(LogTemp, Warning, TEXT("Plz Override PlayAttackMontage()"));
	ParentAnimInstance->Montage_Play(AttackMontage, 1.0f);
}

void UAttackBehavior::JumpToAttackMontageSection(int32 NewSection)
{
	//UE_LOG(LogTemp, Warning, TEXT("Plz Override JumpToAttackMontageSection()"));
	ParentAnimInstance->Montage_SetNextSection(GetAttackMontageSectionName(NewSection - 1), GetAttackMontageSectionName(NewSection), AttackMontage);
}

FName UAttackBehavior::GetAttackMontageSectionName(int32 Section)
{
	return FName(*FString::Printf(TEXT("Attack%d"), Section));
}

