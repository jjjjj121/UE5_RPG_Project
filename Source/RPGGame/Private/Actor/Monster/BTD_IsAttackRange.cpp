// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Monster/BTD_IsAttackRange.h"
#include "Actor/Monster/MonsterAIController.h"
#include "RPGGame/RPGGameCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"
#include "Actor/Monster/Monster_AI.h"

UBTD_IsAttackRange::UBTD_IsAttackRange()
{
	NodeName = TEXT("CanAttack");

}

bool UBTD_IsAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool Result = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
	auto ControllingPawn = Cast<AMonster_AI>(Controller->GetPawn());

	if (ControllingPawn == nullptr) {
		//Enemy �ʱ�ȭ ���� �� ���� ��ȯ
		UE_LOG(LogTemp, Warning, TEXT("ControllingPawn Init Failed : CanAttack_Decorator"));
		return false;
	}

	auto Target = Cast<ARPGGameCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AMonsterAIController::Key_Target));
	if (Target == nullptr) {
		return false;
	}

	
	//���� �þ� �������� ���� �ȿ� ���� �� �����Ƿ� �þ� ���� �ȿ����� �����ϵ��� ����
	Result = (Target->GetDistanceTo(ControllingPawn) <= 200.0f) && OwnerComp.GetBlackboardComponent()->GetValueAsBool(AMonsterAIController::Key_CanSeePlayer);

	//OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::Key_CanAttackRange, Result);
	//UE_LOG(LogTemp, Warning, TEXT("IS ATTACK RANGE RESULT : %d"), Result);

	return Result;
}
