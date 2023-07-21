// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Monster/BTTN_Turn.h"
#include "Actor/Monster/MonsterAIController.h"
#include "Actor/Monster/Monster_AI.h"
#include "RPGGame/RPGGameCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Actor/Monster/MonsterAnimInstance.h"
UBTTN_Turn::UBTTN_Turn(FObjectInitializer const& object_initializer)
{
	bNotifyTick = true;
	NodeName = TEXT("Turn to Target");
}

EBTNodeResult::Type UBTTN_Turn::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
	ControllingPawn = Cast<AMonster_AI>(Controller->GetPawn());

	if (ControllingPawn == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("ControllingPawn Init Failed : Attack_Task"));
		return EBTNodeResult::Failed;
	}

	auto Target = Cast<ARPGGameCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AMonsterAIController::Key_Target));

	if (Target == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Failed?"));
		return EBTNodeResult::Failed;
	};


	TargetRotator = UKismetMathLibrary::FindLookAtRotation(ControllingPawn->GetActorLocation(), Target->GetActorLocation());
	
	return EBTNodeResult::InProgress;
}

void UBTTN_Turn::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	//러프하게 회전
	if (ControllingPawn) {
		//Anim Notify로 Truning Point 설정
		if (ControllingPawn->MonsterAnimInstance->TurningNotify) {
			ControllingPawn->SetActorRotation(FMath::RInterpTo(ControllingPawn->GetActorRotation(), TargetRotator, GetWorld()->GetDeltaSeconds(), RotateSpeed));
		}
		else {
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}
	

}
