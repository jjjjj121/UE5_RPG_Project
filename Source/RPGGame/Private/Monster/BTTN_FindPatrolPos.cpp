// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/BTTN_FindPatrolPos.h"
#include "Monster/MonsterAIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTN_FindPatrolPos::UBTTN_FindPatrolPos(FObjectInitializer const& object_initializer)
{
	//Editor���� ������ TakskNode �̸�
	NodeName = TEXT("FindPatrolPos");
}

EBTNodeResult::Type UBTTN_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
	auto ControllingPawn = Controller->GetPawn();

	if (ControllingPawn == nullptr) {
		//Enemy �ʱ�ȭ ���� �� ���� ��ȯ
		UE_LOG(LogTemp, Warning, TEXT("ControllingPawn Init Failed : FindPatrolPos_Task"));
		return EBTNodeResult::Failed;
	}

	//���� ������� ������ Navi Mesh�� �ʱ�ȭ
	//4.20 �������� UNavigationSystem dms UNavigationSystemV1�� �ٲ�
	UNavigationSystemV1* const NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (NavSystem == nullptr) {
		//navi mesh�� ã�� ���� ��� ���� ��ȯ
		UE_LOG(LogTemp, Warning, TEXT("Find Navimesh Failed : FindPatrolPos_Task"));
		return EBTNodeResult::Failed;
	}

	//Blackboard�� Homepos �����ͼ� ����
	FVector const Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AMonsterAIController::Key_HomePos);
	FNavLocation NextPatrol;

	//NextPatrol �� Random Location ������ ���� �� Key_TargetLocation�� Value�� �ش� ���� ������Ʈ
	if (NavSystem->GetRandomPointInNavigableRadius(Origin, Search_radius, NextPatrol)) {
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(AMonsterAIController::Key_Patrol, NextPatrol.Location);

		//Task ���Ḧ �˸�
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		UE_LOG(LogTemp, Warning, TEXT("TASK SUCCEED"));
		return EBTNodeResult::Succeeded;
	}



	return EBTNodeResult::Failed;
	
	/*
	EBTNodeResult Type : �Լ� ���� ����
	Aborted : Task ���� �� �ߴ�(����)
	Failed : ���� ������ ����
	Succeded : �����ϰ� ����
	InProgress : �½�ũ�� ���� ��, ���� ����� ���� �˷��ش�.
	*/

}
