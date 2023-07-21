// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Monster/BTTN_Attack.h"
#include "Actor/Monster/MonsterAIController.h"
#include "Actor/Monster/Monster_AI.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTN_Attack::UBTTN_Attack(FObjectInitializer const& object_initializer)
{
	bNotifyTick = true;	//tick 활성화
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTTN_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	auto Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
	ControllingPawn = Cast<AMonster_AI>(Controller->GetPawn());

	if (ControllingPawn == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("ControllingPawn Init Failed : Attack_Task"));
		return EBTNodeResult::Failed;
	}

	ControllingPawn->Attack();

	//공격이 끝날 때까지 지연
	return EBTNodeResult::InProgress;
}

//공격이 끝났는지 체크
void UBTTN_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (ControllingPawn) {
		if (!ControllingPawn->GetIsAttacking()) {
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				UE_LOG(LogTemp, Warning, TEXT("MONSTER ATTACK FINISHED"));
		}
		else {
			ControllingPawn->Attack();
		}
	}

}
