// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Monster/BTD_IsAttackRange.h"
#include "Actor/Monster/MonsterAIController.h"
#include "RPGGame/RPGGameCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTD_IsAttackRange::UBTD_IsAttackRange()
{
	NodeName = TEXT("CanAttack");
}

bool UBTD_IsAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool Result = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
	auto ControllingPawn = Controller->GetPawn();

	if (ControllingPawn == nullptr) {
		//Enemy 초기화 실패 시 실패 반환
		UE_LOG(LogTemp, Warning, TEXT("ControllingPawn Init Failed : CanAttack_Decorator"));
		return false;
	}

	auto Target = Cast<ARPGGameCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AMonsterAIController::Key_Target));
	if (Target == nullptr) {
		return false;
	}

	Result = (Target->GetDistanceTo(ControllingPawn) <= 200.0f);

	return Result;
}
