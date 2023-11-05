// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/BTTN_HitReaction.h"
#include "Monster/MonsterAIController.h"
#include "Monster/Monster_AI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

UBTTN_HitReaction::UBTTN_HitReaction(FObjectInitializer const& object_initializer)
{
}

EBTNodeResult::Type UBTTN_HitReaction::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	//auto Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
	//auto ControllingPawn = Cast<AMonster_AI>(Controller->GetPawn());
	//auto Blackborad = Controller->GetBlackboardComponent();

	//AActor* Target = Cast<AActor>(Blackborad->GetValueAsObject(AMonsterAIController::Key_Target));
	//
	//FRotator Delta_A = UKismetMathLibrary::FindLookAtRotation(ControllingPawn->GetActorLocation(), Target->GetActorLocation());
	//FRotator Delta_B = ControllingPawn->GetActorRotation();
	//FRotator Delta_Rotator = UKismetMathLibrary::NormalizedDeltaRotator(Delta_A, Delta_B);

	//int32 Direction_Index = CalculateDirectionIndex(Delta_Rotator.Yaw);
	//FName SectionName = FName(*FString::Printf(TEXT("Reaction%d"), Direction_Index));

	//ControllingPawn->HitReaction(SectionName);

	//if (!Blackborad->GetValueAsBool(AMonsterAIController::Key_IsDead)) {
	//	
	//}
	///*Monster Dead*/
	//else {
	//	//Do Death
	//	UE_LOG(LogTemp, Warning, TEXT("Monster Death"));
	//	//DoDeath(Direction_Index);
	//}

	return EBTNodeResult::InProgress;
}

void UBTTN_HitReaction::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

}

int32 UBTTN_HitReaction::CalculateDirectionIndex(float Direction)
{
	/*Hit Front*/
	if (Direction >= -45.f && Direction <= 45.f) {
		UE_LOG(LogTemp, Warning, TEXT("MONSTER HTI Front"));
		return 1;
	}
	/*Hit Right*/
	else if (Direction > 45.f && Direction <= 135.f) {
		UE_LOG(LogTemp, Warning, TEXT("MONSTER HTI Right"));
		return 2;
	}
	/*Hit Left*/
	else if (Direction >= -135.f && Direction < -45.f) {
		UE_LOG(LogTemp, Warning, TEXT("MONSTER HTI Left"));
		return 3;
	}
	/*Hit Back*/
	else if ((Direction >= -180.f && Direction < -135.f) || (Direction >= 135.f && Direction < 180.f)) {
		UE_LOG(LogTemp, Warning, TEXT("MONSTER HTI Back"));
		return 4;
	}

	/*Error*/
	return -1;
}