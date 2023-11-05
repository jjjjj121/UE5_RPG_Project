// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/BTTN_FindPatrolPos.h"
#include "Monster/MonsterAIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTN_FindPatrolPos::UBTTN_FindPatrolPos(FObjectInitializer const& object_initializer)
{
	//Editor에서 보여질 TakskNode 이름
	NodeName = TEXT("FindPatrolPos");
}

EBTNodeResult::Type UBTTN_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
	auto ControllingPawn = Controller->GetPawn();

	if (ControllingPawn == nullptr) {
		//Enemy 초기화 실패 시 실패 반환
		UE_LOG(LogTemp, Warning, TEXT("ControllingPawn Init Failed : FindPatrolPos_Task"));
		return EBTNodeResult::Failed;
	}

	//현재 에디어테 설정된 Navi Mesh로 초기화
	//4.20 버전부터 UNavigationSystem dms UNavigationSystemV1로 바뀜
	UNavigationSystemV1* const NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (NavSystem == nullptr) {
		//navi mesh를 찾지 못한 경우 실패 반환
		UE_LOG(LogTemp, Warning, TEXT("Find Navimesh Failed : FindPatrolPos_Task"));
		return EBTNodeResult::Failed;
	}

	//Blackboard에 Homepos 가져와서 저장
	FVector const Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AMonsterAIController::Key_HomePos);
	FNavLocation NextPatrol;

	//NextPatrol 에 Random Location 데이터 설정 후 Key_TargetLocation의 Value에 해당 값을 업데이트
	if (NavSystem->GetRandomPointInNavigableRadius(Origin, Search_radius, NextPatrol)) {
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(AMonsterAIController::Key_Patrol, NextPatrol.Location);

		//Task 종료를 알림
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		UE_LOG(LogTemp, Warning, TEXT("TASK SUCCEED"));
		return EBTNodeResult::Succeeded;
	}



	return EBTNodeResult::Failed;
	
	/*
	EBTNodeResult Type : 함수 성공 유무
	Aborted : Task 실행 중 중단(실패)
	Failed : 수행 했으나 실패
	Succeded : 수행하고 성공
	InProgress : 태스크를 수행 중, 실행 결과는 추후 알려준다.
	*/

}
