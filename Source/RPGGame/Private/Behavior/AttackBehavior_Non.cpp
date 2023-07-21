// Fill out your copyright notice in the Description page of Project Settings.


#include "Behavior/AttackBehavior_Non.h"



UAttackBehavior_Non::UAttackBehavior_Non()
{
	//Montage ��������
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack_Montage(TEXT("/Game/Asset/Warrior/RootBone/Non_Animation/Montage/AM_Non_Attack.AM_Non_Attack"));
	if (Attack_Montage.Succeeded()) {
		AttackMontage = Attack_Montage.Object;
		UE_LOG(LogTemp, Warning, TEXT("SET MONTAGE SUCCEEDED"));
	}

	//MaxCombo ����
	MaxCombo = 3;
}

