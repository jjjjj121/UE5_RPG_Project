// Fill out your copyright notice in the Description page of Project Settings.


#include "Behavior/AttackBehavior_GS.h"

UAttackBehavior_GS::UAttackBehavior_GS()
{
	//Montage 가져오기
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack_Montage(TEXT("/Game/Asset/Warrior/RootBone/GS_Animation/Montage/AM_GS_Attack.AM_GS_Attack"));
	if (Attack_Montage.Succeeded()) {
		AttackMontage = Attack_Montage.Object;
		UE_LOG(LogTemp, Warning, TEXT("SET MONTAGE SUCCEEDED"));
	}

	//MaxCombo 설정
	MaxCombo = 3;
}
