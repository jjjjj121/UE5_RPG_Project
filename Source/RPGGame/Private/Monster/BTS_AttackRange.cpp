// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/BTS_AttackRange.h"
#include "Monster/MonsterAIController.h"
#include "RPGGame/RPGGameCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTS_AttackRange::UBTS_AttackRange(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Check Attack Range");
	//Interval = 0.1f;
}

void UBTS_AttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
	auto ControllingPawn = Controller->GetPawn();
	if (ControllingPawn == nullptr) return;

	UWorld* World = ControllingPawn->GetWorld();
	if (World == nullptr) return;


	auto Target = Cast<ARPGGameCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AMonsterAIController::Key_Target));
	if (Target == nullptr) {
		return;
	}

	//몬스터 시야 밖이지만 범위 안에 있을 수 있으므로 시야 범위 안에서만 가능하도록 설정
	UE_LOG(LogTemp, Warning, TEXT("DISTANCE : %f"), Target->GetDistanceTo(ControllingPawn));
	bool Result = (Target->GetDistanceTo(ControllingPawn) <= 200.0f) && OwnerComp.GetBlackboardComponent()->GetValueAsBool(AMonsterAIController::Key_CanSeePlayer);

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::Key_CanAttackRange, Result);
}
