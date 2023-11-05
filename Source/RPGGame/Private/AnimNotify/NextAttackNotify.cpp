// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/NextAttackNotify.h"
#include "Monster/Monster_AI.h"
#include "Monster/MonsterAnimInstance.h"

void UNextAttackNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	AMonster_AI* OwnerMonster = Cast<AMonster_AI>(MeshComp->GetOwner());

	if (OwnerMonster) {
		OwnerMonster->CanNextCombo = true;

		//Attack �� Truning �ñ⸦ ����
		OwnerMonster->MonsterAnimInstance->TurningNotify = true;
	}

}

void UNextAttackNotify::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	AMonster_AI* OwnerMonster = Cast<AMonster_AI>(MeshComp->GetOwner());

	if (OwnerMonster) {
		UE_LOG(LogTemp, Warning, TEXT("NEXT ATTACK BROADCAST"));
		OwnerMonster->MonsterAnimInstance->OnNextAttack.Broadcast();

		//Attack �� Truning �ñ⸦ ����
		OwnerMonster->MonsterAnimInstance->TurningNotify = false;
	}
}
