// Fill out your copyright notice in the Description page of Project Settings.


#include "Behavior/Monster/MutantAttackBehavior.h"

UMutantAttackBehavior::UMutantAttackBehavior()
{
	//Montage ��������
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack_Montage(TEXT("/Game/Asset/Monster/Mutant/Rootbone/Animation/Mutant_Swiping_Montage.Mutant_Swiping_Montage"));
	if (Attack_Montage.Succeeded()) {
		AttackMontage = Attack_Montage.Object;
		UE_LOG(LogTemp, Warning, TEXT("SET MONTAGE SUCCEEDED"));
	}

	//MaxCombo ����
	MaxCombo = 3;
}
